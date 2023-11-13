#!/bin/bash

# Script to install send_to_nextcloud.py and nextcloud_share_link_generator.py, and required packages

# Install necessary packages
sudo apt-get update
sudo apt-get install python3-nautilus python3-gi libnotify-bin python3-pip python3-requests python3-pyperclip -y

# Copy the python scripts to nautilus extensions directory
mkdir -p $HOME/.local/share/nautilus-python/extensions
cp send_to_nextcloud.py $HOME/.local/share/nautilus-python/extensions/
cp nextcloud_share_link_generator.py $HOME/.local/share/nautilus-python/extensions/

# Restart Nautilus
nautilus -q && nautilus &

