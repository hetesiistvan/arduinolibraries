#!/bin/sh

set -e

/setup-ssh-key.sh

ssh -T git@gitlab.com