#!/bin/bash
##############################################################################
# File       : docker_start.sh - Docker Service start
# Domain     : QPF.scripts
# Version    : 2.0
# Date       : 2016/09/01
# Copyright (C) 2015-2018 J C Gonzalez
#_____________________________________________________________________________
# Purpose    : Docker Service start
# Created by : J C Gonzalez
# Status     : Prototype
# History    : See <Changelog>
###############################################################################

# Add the docker group if it doesn't already exist
sudo groupadd docker

# Add the connected user "$USER" to the docker group
sudo gpasswd -a $USER docker

# Update env.
newgrp docker

# Start service docker
service docker start
#sudo service docker start


