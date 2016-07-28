#!/bin/sh
export VOLK_GENERIC=1
export GR_DONT_LOAD_PREFS=1
export srcdir=/usr/local/src/gr-ieee80211ah/lib
export GR_CONF_CONTROLPORT_ON=False
export PATH=/usr/local/src/gr-ieee80211ah/lib:$PATH
export LD_LIBRARY_PATH=/usr/local/src/gr-ieee80211ah/lib:$LD_LIBRARY_PATH
export PYTHONPATH=$PYTHONPATH
test-ieee80211ah 
