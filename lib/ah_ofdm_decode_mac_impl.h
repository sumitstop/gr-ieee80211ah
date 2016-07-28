/* -*- c++ -*- */
/* 
 * Copyright 2016 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_IEEE80211AH_AH_OFDM_DECODE_MAC_IMPL_H
#define INCLUDED_IEEE80211AH_AH_OFDM_DECODE_MAC_IMPL_H

#include <ieee80211ah/ah_ofdm_decode_mac.h>

#include "utils_ah.h"
#include <boost/crc.hpp>
#include <itpp/itcomm.h>
#include <iomanip>

namespace gr {
  namespace ieee80211ah {
  	  using namespace itpp;

    class ah_ofdm_decode_mac_impl : public ah_ofdm_decode_mac
    {
     private:
     	gr_complex sym[1000 * 48 * 100];
     	vec bits;
     	double deinter[1000 * 48];
     	char out_bits[40000];
     	char out_bytes[40000];
     	bvec decoded_bits;

     	bool d_debug;
     	bool d_log;
     	tx_param d_tx;
     	ofdm_param d_ofdm;
     	int copied;
     	bool d_frame_complete;

     	Modulator<std::complex<double> > bpsk;
     	Modulator<std::complex<double> > qpsk;
     	Modulator<std::complex<double> > qam16;
     	Modulator<std::complex<double> > qam64;
     	Modulator<std::complex<double> > qam256;

     public:
      ah_ofdm_decode_mac_impl(bool log, bool debug);
      ~ah_ofdm_decode_mac_impl();

      void decode();
      void demodulate();
      void deinterleave();
      void decode_conv();
      void descramble ();
      void print_output();

      // Where all the action really happens
      void forecast (int noutput_items, gr_vector_int &ninput_items_required);

      int general_work(int noutput_items,
           gr_vector_int &ninput_items,
           gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);
    };

  } // namespace ieee80211ah
} // namespace gr

#endif /* INCLUDED_IEEE80211AH_AH_OFDM_DECODE_MAC_IMPL_H */

