
#!/usr/bin/python2

import sys, os, re
sys.path.append('')
os.environ['srcdir'] = '/usr/local/src/gr-ieee80211ah/lib'
os.chdir('/usr/local/src/gr-ieee80211ah/lib')

if __name__ == '__main__':
    sys.path.append('/usr/local/src/gr-ieee80211ah/lib/../python')
    import build_utils
    root, inp = sys.argv[1:3]
    for sig in sys.argv[3:]:
        name = re.sub ('X+', sig, root)
        d = build_utils.standard_dict(name, sig, 'ieee80211ah')
        build_utils.expand_template(d, inp, '_impl')
