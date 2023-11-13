import os
import shutil
import subprocess
import gi

gi.require_version('Nautilus', '3.0')
gi.require_version('Notify', '0.7')

from gi.repository import Nautilus, GObject, GLib, Notify

class SendToNextcloudExtension(GObject.GObject, Nautilus.MenuProvider):
    
    def __init__(self):
        Notify.init("SendToNextcloudExtension")
    
    def send_notification(self, title, text):
        """Send a desktop notification."""
        notification = Notify.Notification.new(title, text)
        notification.show()

    def perform_action(self, menu, files, action):
        """Generic function to perform the specified action."""
        nextcloud_directory = os.path.join(os.environ['HOME'], 'Nextcloud')
        
        for file in files:
            try:
                if file.is_directory():
                    continue

                file_path = file.get_location().get_path()
                target_path = os.path.join(nextcloud_directory, os.path.basename(file_path))

                # If the file already exists in the target directory, ask for overwrite confirmation
                if os.path.exists(target_path):
                    response = subprocess.run(
                        ['zenity', '--question', '--title=Confirmation', 
                         '--text=File already exists. Overwrite?'],
                        capture_output=True
                    )
                    # If the user selects 'No', do not proceed with move/copy
                    if response.returncode != 0:
                        self.send_notification("Send to Nextcloud", f"Operation canceled for {os.path.basename(file_path)}.")
                        continue

                # Perform the action (move or copy)
                if action == 'move':
                    shutil.move(file_path, target_path)
                    action_text = "Moved"
                elif action == 'copy':
                    shutil.copy(file_path, target_path)
                    action_text = "Copied"

                self.send_notification("Send to Nextcloud", f"{action_text} {os.path.basename(file_path)} to Nextcloud directory.")

            except Exception as e:
                self.send_notification("Send to Nextcloud - Error", f"Failed to {action} {os.path.basename(file_path)}: {str(e)}")

    def get_file_items(self, window, files):
        """Create the right-click menu entries."""
        if not files:
            return []

        nextcloud_directory = os.path.join(os.environ['HOME'], 'Nextcloud')
        items = []

        for file in files:
            file_path = file.get_location().get_path()
            # Check if the file is in the Nextcloud directory
            if file_path.startswith(nextcloud_directory):
                continue  # Skip adding menu items for files inside Nextcloud directory

            move_item = Nautilus.MenuItem(
                name='SendToNextcloud::move_to_nextcloud',
                label='Move to Nextcloud',
                tip='Move this file to your Nextcloud folder'
            )
            move_item.connect('activate', self.perform_action, files, 'move')
            items.append(move_item)

            copy_item = Nautilus.MenuItem(
                name='SendToNextcloud::copy_to_nextcloud',
                label='Copy to Nextcloud',
                tip='Copy this file to your Nextcloud folder'
            )
            copy_item.connect('activate', self.perform_action, files, 'copy')
            items.append(copy_item)

        return items

