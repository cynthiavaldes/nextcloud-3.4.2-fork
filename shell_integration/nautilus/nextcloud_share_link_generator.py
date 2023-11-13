import os
import configparser
import urllib.parse
import requests
import gi
gi.require_version('Nautilus', '3.0')
from gi.repository import Nautilus, GObject, Gtk
import pyperclip

class NextcloudShareLinkExtension(GObject.GObject, Nautilus.MenuProvider):
    
    def __init__(self):
        self.nextcloud_url = ""
        self.username = ""
        self.password = ""
        self.credentials_file = os.path.join(os.path.expanduser('~'), '.nextcloud_credentials.txt')

        # Reading Nextcloud configuration
        config = configparser.ConfigParser()
        config_path = os.path.join(os.path.expanduser('~'), '.config', 'Nextcloud', 'nextcloud.cfg')
        if os.path.exists(config_path):
            config.read(config_path)
            self.nextcloud_url = config.get('Accounts', '0\\url', fallback='')
            self.username = config.get('Accounts', '0\\webflow_user', fallback='')
            self.password = self.get_stored_password()
        else:
            # Default values if the config file is not found
            self.nextcloud_url = "https://your-nextcloud-instance.com"

    def prompt_credentials(self):
        dialog = Gtk.MessageDialog(
            None,
            Gtk.DialogFlags.MODAL,
            Gtk.MessageType.QUESTION,
            Gtk.ButtonsType.OK_CANCEL,
            "Please enter your Nextcloud credentials"
        )
        dialog.set_title("Nextcloud Login")

        # Create entry fields
        entry_username = Gtk.Entry()
        entry_password = Gtk.Entry()
        entry_password.set_visibility(False)
        entry_password.set_invisible_char("*")

        # Add fields to dialog
        dialog.vbox.pack_start(Gtk.Label("Username:"), True, True, 0)
        dialog.vbox.pack_start(entry_username, True, True, 0)
        dialog.vbox.pack_start(Gtk.Label("Password:"), True, True, 0)
        dialog.vbox.pack_start(entry_password, True, True, 0)
        
        dialog.show_all()

        response = dialog.run()
        username = entry_username.get_text()
        password = entry_password.get_text()

        dialog.destroy()

        if response == Gtk.ResponseType.OK:
            return username, password
        return None, None

    def store_credentials(self):
        with open(self.credentials_file, 'w') as file:
            file.write(f"{self.username}\n{self.password}")

    def get_stored_password(self):
        if os.path.exists(self.credentials_file):
            with open(self.credentials_file, 'r') as file:
                lines = file.readlines()
                if len(lines) >= 2:
                    return lines[1].strip()
        return None

    def get_file_items(self, window, files):
        if len(files) != 1:
            return

        file = files[0]
        if file.is_directory() or not file.get_uri().startswith(f"file://{os.path.expanduser('~')}/Nextcloud"):
            return

        item = Nautilus.MenuItem(
            name="NextcloudShareLinkExtension::ShareLink",
            label="Generate Nextcloud Share Link",
            tip="Generate a shareable link for this file"
        )
        item.connect('activate', self.generate_share_link, file)
        return [item]

    def generate_share_link(self, menu, file):
        if not self.username or not self.password:
            self.username, self.password = self.prompt_credentials()
            if not self.username or not self.password:
                self.show_notification("Nextcloud credentials are required.")
                return
            self.store_credentials()

        file_path = file.get_location().get_path()
        relative_path = os.path.relpath(file_path, os.path.expanduser('~/Nextcloud'))
        encoded_path = urllib.parse.quote(relative_path)

        url = f"{self.nextcloud_url}/ocs/v2.php/apps/files_sharing/api/v1/shares?format=json"
        data = {
            'path': encoded_path,
            'shareType': 3
        }
        headers = {
            'OCS-APIRequest': 'true'
        }

        response = requests.post(url, auth=(self.username, self.password), data=data, headers=headers)

        if response.status_code == 200:
            share_link = response.json().get('ocs', {}).get('data', {}).get('url')
            if share_link:
                pyperclip.copy(share_link)
                self.show_notification("Link copied to clipboard!")
            else:
                self.show_notification("Failed to get share link.")
        else:
            self.show_notification("Error generating share link.")

    def show_notification(self, message):
        dialog = Gtk.MessageDialog(
            transient_for=None,
            flags=0,
            message_type=Gtk.MessageType.INFO,
            buttons=Gtk.ButtonsType.OK,
            text=message,
        )
        dialog.run()
        dialog.destroy()

# Add the extension to Nautilus
GObject.type_register(NextcloudShareLinkExtension)





