#!/usr/bin/env python2
# -*- coding: utf-8 -*-
##################################################
# GNU Radio Python Flow Graph
# Title: Wifi Loopback Ah
# Generated: Mon Aug 22 15:10:13 2016
##################################################

if __name__ == '__main__':
    import ctypes
    import sys
    if sys.platform.startswith('linux'):
        try:
            x11 = ctypes.cdll.LoadLibrary('libX11.so')
            x11.XInitThreads()
        except:
            print "Warning: failed to XInitThreads()"

import os
import sys
sys.path.append(os.environ.get('GRC_HIER_PATH', os.path.expanduser('~/.grc_gnuradio')))

from gnuradio import blocks
from gnuradio import channels
from gnuradio import eng_notation
from gnuradio import gr
from gnuradio import wxgui
from gnuradio.eng_option import eng_option
from gnuradio.filter import firdes
from gnuradio.wxgui import forms
from gnuradio.wxgui import numbersink2
from gnuradio.wxgui import scopesink2
from grc_gnuradio import wxgui as grc_wxgui
from optparse import OptionParser
from wifi_phy_hier_ah import wifi_phy_hier_ah  # grc-generated hier_block
import foo
import ieee802_11
import pmt
import wx


class wifi_loopback_ah(grc_wxgui.top_block_gui):

    def __init__(self):
        grc_wxgui.top_block_gui.__init__(self, title="Wifi Loopback Ah")

        ##################################################
        # Variables
        ##################################################
        self.snr = snr = 20
        self.pdu_length = pdu_length = 500
        self.out_buf_size = out_buf_size = 96000
        self.interval = interval = 100
        self.encoding = encoding = 0
        self.chan_est = chan_est = 1

        ##################################################
        # Blocks
        ##################################################
        _snr_sizer = wx.BoxSizer(wx.VERTICAL)
        self._snr_text_box = forms.text_box(
        	parent=self.GetWin(),
        	sizer=_snr_sizer,
        	value=self.snr,
        	callback=self.set_snr,
        	label='snr',
        	converter=forms.float_converter(),
        	proportion=0,
        )
        self._snr_slider = forms.slider(
        	parent=self.GetWin(),
        	sizer=_snr_sizer,
        	value=self.snr,
        	callback=self.set_snr,
        	minimum=-15,
        	maximum=30,
        	num_steps=1000,
        	style=wx.SL_HORIZONTAL,
        	cast=float,
        	proportion=1,
        )
        self.Add(_snr_sizer)
        _pdu_length_sizer = wx.BoxSizer(wx.VERTICAL)
        self._pdu_length_text_box = forms.text_box(
        	parent=self.GetWin(),
        	sizer=_pdu_length_sizer,
        	value=self.pdu_length,
        	callback=self.set_pdu_length,
        	label='pdu_length',
        	converter=forms.int_converter(),
        	proportion=0,
        )
        self._pdu_length_slider = forms.slider(
        	parent=self.GetWin(),
        	sizer=_pdu_length_sizer,
        	value=self.pdu_length,
        	callback=self.set_pdu_length,
        	minimum=0,
        	maximum=1500,
        	num_steps=1000,
        	style=wx.SL_HORIZONTAL,
        	cast=int,
        	proportion=1,
        )
        self.Add(_pdu_length_sizer)
        _interval_sizer = wx.BoxSizer(wx.VERTICAL)
        self._interval_text_box = forms.text_box(
        	parent=self.GetWin(),
        	sizer=_interval_sizer,
        	value=self.interval,
        	callback=self.set_interval,
        	label="PDU Interval (ms)",
        	converter=forms.int_converter(),
        	proportion=0,
        )
        self._interval_slider = forms.slider(
        	parent=self.GetWin(),
        	sizer=_interval_sizer,
        	value=self.interval,
        	callback=self.set_interval,
        	minimum=10,
        	maximum=1000,
        	num_steps=1000,
        	style=wx.SL_HORIZONTAL,
        	cast=int,
        	proportion=1,
        )
        self.Add(_interval_sizer)
        self._encoding_chooser = forms.radio_buttons(
        	parent=self.GetWin(),
        	value=self.encoding,
        	callback=self.set_encoding,
        	label="Encoding",
        	choices=[0,1,2,3,4,5,6,7,8],
        	labels=["BPSK 1/2", "QPSK 1/2", "QPSK 3/4",  "16QAM 1/2", "16QAM 3/4", "64QAM 2/3", "64QAM 3/4", "64QAM 5/6", "256QAM 3/4"  ],
        	style=wx.RA_HORIZONTAL,
        )
        self.Add(self._encoding_chooser)
        self._chan_est_chooser = forms.radio_buttons(
        	parent=self.GetWin(),
        	value=self.chan_est,
        	callback=self.set_chan_est,
        	label='chan_est',
        	choices=[0, 1],
        	labels=["LMS", "Linear Comb"],
        	style=wx.RA_HORIZONTAL,
        )
        self.Add(self._chan_est_chooser)
        self.wxgui_scopesink2_0 = scopesink2.scope_sink_c(
        	self.GetWin(),
        	title="Scope Plot",
        	sample_rate=12500,
        	v_scale=0,
        	v_offset=0,
        	t_scale=0,
        	ac_couple=False,
        	xy_mode=True,
        	num_inputs=1,
        	trig_mode=wxgui.TRIG_MODE_AUTO,
        	y_axis_label="Counts",
        )
        self.Add(self.wxgui_scopesink2_0.win)
        self.wxgui_numbersink2_0 = numbersink2.number_sink_f(
        	self.GetWin(),
        	unit="%",
        	minval=0,
        	maxval=100,
        	factor=1.0,
        	decimal_places=2,
        	ref_level=0,
        	sample_rate=1,
        	number_rate=15,
        	average=True,
        	avg_alpha=0.02,
        	label="Frame Error Rate",
        	peak_hold=False,
        	show_gauge=True,
        )
        self.Add(self.wxgui_numbersink2_0.win)
        self.wifi_phy_hier_ah_0 = wifi_phy_hier_ah(
            chan_est=chan_est,
            encoding=encoding,
            sensitivity=0.56,
        )
        self.ieee802_11_ofdm_parse_mac_0 = ieee802_11.ofdm_parse_mac(False, True)
        self.ieee802_11_ofdm_mac_0 = ieee802_11.ofdm_mac(([0x23, 0x23, 0x23, 0x23, 0x23, 0x23]), ([0x42, 0x42, 0x42, 0x42, 0x42, 0x42]), ([0xff, 0xff, 0xff, 0xff, 0xff, 0xff]))
        self.foo_packet_pad2_0 = foo.packet_pad2(False, False, 0.001, 500, 0)
        (self.foo_packet_pad2_0).set_min_output_buffer(96000)
        self.channels_channel_model_0 = channels.channel_model(
        	noise_voltage=1,
        	frequency_offset=0,
        	epsilon=1.0,
        	taps=(1.0, ),
        	noise_seed=0,
        	block_tags=False
        )
        self.blocks_pdu_to_tagged_stream_0 = blocks.pdu_to_tagged_stream(blocks.float_t, "packet_len")
        self.blocks_multiply_const_vxx_0 = blocks.multiply_const_vcc(((10**(snr/10.0))**.5, ))
        self.blocks_message_strobe_0 = blocks.message_strobe(pmt.intern("".join("x" for i in range(pdu_length))), interval)

        ##################################################
        # Connections
        ##################################################
        self.msg_connect((self.blocks_message_strobe_0, 'strobe'), (self.ieee802_11_ofdm_mac_0, 'app in'))    
        self.msg_connect((self.ieee802_11_ofdm_mac_0, 'phy out'), (self.wifi_phy_hier_ah_0, 'mac_in'))    
        self.msg_connect((self.ieee802_11_ofdm_parse_mac_0, 'fer'), (self.blocks_pdu_to_tagged_stream_0, 'pdus'))    
        self.msg_connect((self.wifi_phy_hier_ah_0, 'mac_out'), (self.ieee802_11_ofdm_parse_mac_0, 'in'))    
        self.connect((self.blocks_multiply_const_vxx_0, 0), (self.channels_channel_model_0, 0))    
        self.connect((self.blocks_pdu_to_tagged_stream_0, 0), (self.wxgui_numbersink2_0, 0))    
        self.connect((self.channels_channel_model_0, 0), (self.wifi_phy_hier_ah_0, 0))    
        self.connect((self.foo_packet_pad2_0, 0), (self.blocks_multiply_const_vxx_0, 0))    
        self.connect((self.wifi_phy_hier_ah_0, 0), (self.foo_packet_pad2_0, 0))    
        self.connect((self.wifi_phy_hier_ah_0, 1), (self.wxgui_scopesink2_0, 0))    

    def get_snr(self):
        return self.snr

    def set_snr(self, snr):
        self.snr = snr
        self._snr_slider.set_value(self.snr)
        self._snr_text_box.set_value(self.snr)
        self.blocks_multiply_const_vxx_0.set_k(((10**(self.snr/10.0))**.5, ))

    def get_pdu_length(self):
        return self.pdu_length

    def set_pdu_length(self, pdu_length):
        self.pdu_length = pdu_length
        self._pdu_length_slider.set_value(self.pdu_length)
        self._pdu_length_text_box.set_value(self.pdu_length)
        self.blocks_message_strobe_0.set_msg(pmt.intern("".join("x" for i in range(self.pdu_length))))

    def get_out_buf_size(self):
        return self.out_buf_size

    def set_out_buf_size(self, out_buf_size):
        self.out_buf_size = out_buf_size

    def get_interval(self):
        return self.interval

    def set_interval(self, interval):
        self.interval = interval
        self._interval_slider.set_value(self.interval)
        self._interval_text_box.set_value(self.interval)
        self.blocks_message_strobe_0.set_period(self.interval)

    def get_encoding(self):
        return self.encoding

    def set_encoding(self, encoding):
        self.encoding = encoding
        self._encoding_chooser.set_value(self.encoding)
        self.wifi_phy_hier_ah_0.set_encoding(self.encoding)

    def get_chan_est(self):
        return self.chan_est

    def set_chan_est(self, chan_est):
        self.chan_est = chan_est
        self._chan_est_chooser.set_value(self.chan_est)
        self.wifi_phy_hier_ah_0.set_chan_est(self.chan_est)


def main(top_block_cls=wifi_loopback_ah, options=None):

    tb = top_block_cls()
    tb.Start(True)
    tb.Wait()


if __name__ == '__main__':
    main()
