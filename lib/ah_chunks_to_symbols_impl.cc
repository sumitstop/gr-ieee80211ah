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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "ah_chunks_to_symbols_impl.h"

#include <gnuradio/tag_checker.h>
#include <assert.h>

#include "utils_ah.h"
#include <iostream>

namespace gr {
  namespace ieee80211ah {

    ah_chunks_to_symbols::sptr
    ah_chunks_to_symbols::make()
    {
      return gnuradio::get_initial_sptr(new ah_chunks_to_symbols_impl());
    }

    /*
     * The private constructor
     */
    ah_chunks_to_symbols_impl::ah_chunks_to_symbols_impl()
    :  tagged_stream_block("ah_chunks_to_symbols",
                 gr::io_signature::make(1, 1, sizeof(char)),
                 gr::io_signature::make(1, 1, sizeof(gr_complex)), "packet_len")
       {}

    /*
     * Our virtual destructor.
     */
    ah_chunks_to_symbols_impl::~ah_chunks_to_symbols_impl()
    {
    }

    void
    ah_chunks_to_symbols_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      /* <+forecast+> e.g. ninput_items_required[0] = noutput_items */
    }

    int
    ah_chunks_to_symbols_impl::work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
     const unsigned char *in = (unsigned char*)input_items[0];
     gr_complex *out = (gr_complex*)output_items[0];

     std::vector<tag_t> tags;
         get_tags_in_range(tags, 0, nitems_read(0),
         				nitems_read(0) + ninput_items[0],
         				pmt::mp("encoding"));

    // Tell runtime system how many input items we consumed on
    // each input stream.
    // consume_each (noutput_items);
   	if(tags.size() != 1) {
   		throw std::runtime_error("no encoding in input stream");
   	}

   	Encoding encoding = (Encoding)pmt::to_long(tags[0].value);

   	const gr_complex *mapping;

   	switch (encoding) {
   	case BPSK_1_2:
   	case BPSK_3_4:
   		mapping = BPSK;
   		break;

   	case QPSK_1_2:
   	case QPSK_3_4:
   		mapping = QPSK;
   		break;

   	case QAM16_1_2:
   	case QAM16_3_4:
   		mapping = QAM16;
   		break;

   	case QAM64_2_3:
   	case QAM64_3_4:
   	case QAM64_5_6:
   		mapping = QAM64;
   		break;

   	case QAM256_3_4:
   		mapping = QAM256;
   		break;

   	default:
   		throw std::invalid_argument("wrong encoding");
   		break;
   	}

   	for(int i = 0; i < ninput_items[0]; i++) {
   		out[i] = mapping[in[i]];
   	}

   	    // Tell runtime system how many output items we produced.
   	    return noutput_items;
   	}

   	const gr_complex ah_chunks_to_symbols_impl::BPSK[2] = {
   		gr_complex(-1.0, 0.0), gr_complex(1.0, 0.0)};

   	const gr_complex ah_chunks_to_symbols_impl::QPSK[4] = {
   		gr_complex(-0.7071, -0.7071), gr_complex(-0.7071, 0.7071),
   		gr_complex(+0.7071, -0.7071), gr_complex(+0.7071, 0.7071)};

   	const gr_complex ah_chunks_to_symbols_impl::QAM16[16] = {
   		gr_complex(-0.9487, -0.9487), gr_complex(-0.9487, -0.3162),
   		gr_complex(-0.9487, 0.9487), gr_complex(-0.9487, 0.3162),
  		gr_complex(-0.3162, -0.9487), gr_complex(-0.3162, -0.3162),
   		gr_complex(-0.3162, 0.9487), gr_complex(-0.3162, 0.3162),
   		gr_complex(0.9487, -0.9487), gr_complex(0.9487, -0.3162),
  		gr_complex(0.9487, 0.9487), gr_complex(0.9487, 0.3162),
   		gr_complex(0.3162, -0.9487), gr_complex(0.3162, -0.3162),
   		gr_complex(0.3162, 0.9487), gr_complex(0.3162, 0.3162)};

   const gr_complex ah_chunks_to_symbols_impl::QAM64[64] = {
   		gr_complex(-1.0801, -1.0801), gr_complex(-1.0801, -0.7715),
   		gr_complex(-1.0801, -0.1543), gr_complex(-1.0801, -0.4629),
   		gr_complex(-1.0801, 1.0801), gr_complex(-1.0801, 0.7715),
   		gr_complex(-1.0801, 0.1543), gr_complex(-1.0801, 0.4629),
   		gr_complex(-0.7715, -1.0801), gr_complex(-0.7715, -0.7715),
   		gr_complex(-0.7715, -0.1543), gr_complex(-0.7715, -0.4629),
   		gr_complex(-0.7715, 1.0801), gr_complex(-0.7715, 0.7715),
   		gr_complex(-0.7715, 0.1543), gr_complex(-0.7715, 0.4629),
  		gr_complex(-0.1543, -1.0801), gr_complex(-0.1543, -0.7715),
  		gr_complex(-0.1543, -0.1543), gr_complex(-0.1543, -0.4629),
   		gr_complex(-0.1543, 1.0801), gr_complex(-0.1543, 0.7715),
 		gr_complex(-0.1543, 0.1543), gr_complex(-0.1543, 0.4629),
   		gr_complex(-0.4629, -1.0801), gr_complex(-0.4629, -0.7715),
  		gr_complex(-0.4629, -0.1543), gr_complex(-0.4629, -0.4629),
   		gr_complex(-0.4629, 1.0801), gr_complex(-0.4629, 0.7715),
   		gr_complex(-0.4629, 0.1543), gr_complex(-0.4629, 0.4629),
   		gr_complex(1.0801, -1.0801), gr_complex(1.0801, -0.7715),
   		gr_complex(1.0801, -0.1543), gr_complex(1.0801, -0.4629),
   		gr_complex(1.0801, 1.0801), gr_complex(1.0801, 0.7715),
   		gr_complex(1.0801, 0.1543), gr_complex(1.0801, 0.4629),
   		gr_complex(0.7715, -1.0801), gr_complex(0.7715, -0.7715),
   		gr_complex(0.7715, -0.1543), gr_complex(0.7715, -0.4629),
   		gr_complex(0.7715, 1.0801), gr_complex(0.7715, 0.7715),
   		gr_complex(0.7715, 0.1543), gr_complex(0.7715, 0.4629),
   		gr_complex(0.1543, -1.0801), gr_complex(0.1543, -0.7715),
   		gr_complex(0.1543, -0.1543), gr_complex(0.1543, -0.4629),
   		gr_complex(0.1543, 1.0801), gr_complex(0.1543, 0.7715),
   		gr_complex(0.1543, 0.1543), gr_complex(0.1543, 0.4629),
   		gr_complex(0.4629, -1.0801), gr_complex(0.4629, -0.7715),
   		gr_complex(0.4629, -0.1543), gr_complex(0.4629, -0.4629),
   		gr_complex(0.4629, 1.0801), gr_complex(0.4629, 0.7715),
   		gr_complex(0.4629, 0.1543), gr_complex(0.4629, 0.4629)};

    const gr_complex ah_chunks_to_symbols_impl::QAM256[256] = {
  		gr_complex(-1.1538, -1.1538), gr_complex(-1.1538, -1.0000),
   		gr_complex(-1.1538, -0.8462), gr_complex(-1.1538, -0.6923),
   		gr_complex(-1.1538, -0.5385), gr_complex(-1.1538, -0.3846),
   		gr_complex(-1.1538, -0.2308), gr_complex(-1.1538, -0.0769),
   		gr_complex(-1.1538, 1.1538), gr_complex(-1.1538, 1.0000),
   		gr_complex(-1.1538, 0.8462), gr_complex(-1.1538, 0.6923),
   		gr_complex(-1.1538, 0.5385), gr_complex(-1.1538, 0.3846),
   		gr_complex(-1.1538, 0.2308), gr_complex(-1.1538, 0.0769),
   		gr_complex(-1.0000, -1.1538), gr_complex(-1.0000, -1.0000),
   		gr_complex(-1.0000, -0.8462), gr_complex(-1.0000, -0.6923),
   		gr_complex(-1.0000, -0.5385), gr_complex(-1.0000, -0.3846),
   		gr_complex(-1.0000, -0.2308), gr_complex(-1.0000, -0.0769),
   		gr_complex(-1.0000, 1.1538), gr_complex(-1.0000, 1.0000),
   		gr_complex(-1.0000, 0.8462), gr_complex(-1.0000, 0.6923),
   		gr_complex(-1.0000, 0.5385), gr_complex(-1.0000, 0.3846),
   		gr_complex(-1.0000, 0.2308), gr_complex(-1.0000, 0.0769),
   		gr_complex(-0.8462, -1.1538), gr_complex(-0.8462, -1.0000),
   		gr_complex(-0.8462, -0.8462), gr_complex(-0.8462, -0.6923),
   		gr_complex(-0.8462, -0.5385), gr_complex(-0.8462, -0.3846),
   		gr_complex(-0.8462, -0.2308), gr_complex(-0.8462, -0.0769),
   		gr_complex(-0.8462, 1.1538), gr_complex(-0.8462, 1.0000),
   		gr_complex(-0.8462, 0.8462), gr_complex(-0.8462, 0.6923),
   		gr_complex(-0.8462, 0.5385), gr_complex(-0.8462, 0.3846),
   		gr_complex(-0.8462, 0.2308), gr_complex(-0.8462, 0.0769),
   		gr_complex(-0.6923, -1.1538), gr_complex(-0.6923, -1.0000),
   		gr_complex(-0.6923, -0.8462), gr_complex(-0.6923, -0.6923),
   		gr_complex(-0.6923, -0.5385), gr_complex(-0.6923, -0.3846),
   		gr_complex(-0.6923, -0.2308), gr_complex(-0.6923, -0.0769),
   		gr_complex(-0.6923, 1.1538), gr_complex(-0.6923, 1.0000),
   		gr_complex(-0.6923, 0.8462), gr_complex(-0.6923, 0.6923),
   		gr_complex(-0.6923, 0.5385), gr_complex(-0.6923, 0.3846),
   		gr_complex(-0.6923, 0.2308), gr_complex(-0.6923, 0.0769),
   		gr_complex(-0.5385, -1.1538), gr_complex(-0.5385, -1.0000),
   		gr_complex(-0.5385, -0.8462), gr_complex(-0.5385, -0.6923),
   		gr_complex(-0.5385, -0.5385), gr_complex(-0.5385, -0.3846),
   		gr_complex(-0.5385, -0.2308), gr_complex(-0.5385, -0.0769),
   		gr_complex(-0.5385, 1.1538), gr_complex(-0.5385, 1.0000),
   		gr_complex(-0.5385, 0.8462), gr_complex(-0.5385, 0.6923),
   		gr_complex(-0.5385, 0.5385), gr_complex(-0.5385, 0.3846),
   		gr_complex(-0.5385, 0.2308), gr_complex(-0.5385, 0.0769),
   		gr_complex(-0.3846, -1.1538), gr_complex(-0.3846, -1.0000),
   		gr_complex(-0.3846, -0.8462), gr_complex(-0.3846, -0.6923),
   		gr_complex(-0.3846, -0.5385), gr_complex(-0.3846, -0.3846),
   		gr_complex(-0.3846, -0.2308), gr_complex(-0.3846, -0.0769),
   		gr_complex(-0.3846, 1.1538), gr_complex(-0.3846, 1.0000),
   		gr_complex(-0.3846, 0.8462), gr_complex(-0.3846, 0.6923),
   		gr_complex(-0.3846, 0.5385), gr_complex(-0.3846, 0.3846),
   		gr_complex(-0.3846, 0.2308), gr_complex(-0.3846, 0.0769),
   		gr_complex(-0.2308, -1.1538), gr_complex(-0.2308, -1.0000),
   		gr_complex(-0.2308, -0.8462), gr_complex(-0.2308, -0.6923),
   		gr_complex(-0.2308, -0.5385), gr_complex(-0.2308, -0.3846),
   		gr_complex(-0.2308, -0.2308), gr_complex(-0.2308, -0.0769),
   		gr_complex(-0.2308, 1.1538), gr_complex(-0.2308, 1.0000),
   		gr_complex(-0.2308, 0.8462), gr_complex(-0.2308, 0.6923),
   		gr_complex(-0.2308, 0.5385), gr_complex(-0.2308, 0.3846),
   		gr_complex(-0.2308, 0.2308), gr_complex(-0.2308, 0.0769),
   		gr_complex(-0.0769, -1.1538), gr_complex(-0.0769, -1.0000),
   		gr_complex(-0.0769, -0.8462), gr_complex(-0.0769, -0.6923),
   		gr_complex(-0.0769, -0.5385), gr_complex(-0.0769, -0.3846),
   		gr_complex(-0.0769, -0.2308), gr_complex(-0.0769, -0.0769),
   		gr_complex(-0.0769, 1.1538), gr_complex(-0.0769, 1.0000),
   		gr_complex(-0.0769, 0.8462), gr_complex(-0.0769, 0.6923),
   		gr_complex(-0.0769, 0.5385), gr_complex(-0.0769, 0.3846),
   		gr_complex(-0.0769, 0.2308), gr_complex(-0.0769, 0.0769),
   		gr_complex(1.1538, -1.1538), gr_complex(1.1538, -1.0000),
   		gr_complex(1.1538, -0.8462), gr_complex(1.1538, -0.6923),
   		gr_complex(1.1538, -0.5385), gr_complex(1.1538, -0.3846),
   		gr_complex(1.1538, -0.2308), gr_complex(1.1538, -0.0769),
   		gr_complex(1.1538, 1.1538), gr_complex(1.1538, 1.0000),
   		gr_complex(1.1538, 0.8462), gr_complex(1.1538, 0.6923),
   		gr_complex(1.1538, 0.5385), gr_complex(1.1538, 0.3846),
   		gr_complex(1.1538, 0.2308), gr_complex(1.1538, 0.0769),
   		gr_complex(1.0000, -1.1538), gr_complex(1.0000, -1.0000),
   		gr_complex(1.0000, -0.8462), gr_complex(1.0000, -0.6923),
   		gr_complex(1.0000, -0.5385), gr_complex(1.0000, -0.3846),
   		gr_complex(1.0000, -0.2308), gr_complex(1.0000, -0.0769),
   		gr_complex(1.0000, 1.1538), gr_complex(1.0000, 1.0000),
   		gr_complex(1.0000, 0.8462), gr_complex(1.0000, 0.6923),
   		gr_complex(1.0000, 0.5385), gr_complex(1.0000, 0.3846),
   		gr_complex(1.0000, 0.2308), gr_complex(1.0000, 0.0769),
   		gr_complex(0.8462, -1.1538), gr_complex(0.8462, -1.0000),
   		gr_complex(0.8462, -0.8462), gr_complex(0.8462, -0.6923),
   		gr_complex(0.8462, -0.5385), gr_complex(0.8462, -0.3846),
   		gr_complex(0.8462, -0.2308), gr_complex(0.8462, -0.0769),
   		gr_complex(0.8462, 1.1538), gr_complex(0.8462, 1.0000),
   		gr_complex(0.8462, 0.8462), gr_complex(0.8462, 0.6923),
   		gr_complex(0.8462, 0.5385), gr_complex(0.8462, 0.3846),
   		gr_complex(0.8462, 0.2308), gr_complex(0.8462, 0.0769),
   		gr_complex(0.6923, -1.1538), gr_complex(0.6923, -1.0000),
   		gr_complex(0.6923, -0.8462), gr_complex(0.6923, -0.6923),
   		gr_complex(0.6923, -0.5385), gr_complex(0.6923, -0.3846),
   		gr_complex(0.6923, -0.2308), gr_complex(0.6923, -0.0769),
   		gr_complex(0.6923, 1.1538), gr_complex(0.6923, 1.0000),
   		gr_complex(0.6923, 0.8462), gr_complex(0.6923, 0.6923),
   		gr_complex(0.6923, 0.5385), gr_complex(0.6923, 0.3846),
   		gr_complex(0.6923, 0.2308), gr_complex(0.6923, 0.0769),
   		gr_complex(0.5385, -1.1538), gr_complex(0.5385, -1.0000),
   		gr_complex(0.5385, -0.8462), gr_complex(0.5385, -0.6923),
   		gr_complex(0.5385, -0.5385), gr_complex(0.5385, -0.3846),
   		gr_complex(0.5385, -0.2308), gr_complex(0.5385, -0.0769),
   		gr_complex(0.5385, 1.1538), gr_complex(0.5385, 1.0000),
   		gr_complex(0.5385, 0.8462), gr_complex(0.5385, 0.6923),
   		gr_complex(0.5385, 0.5385), gr_complex(0.5385, 0.3846),
   		gr_complex(0.5385, 0.2308), gr_complex(0.5385, 0.0769),
   		gr_complex(0.3846, -1.1538), gr_complex(0.3846, -1.0000),
   		gr_complex(0.3846, -0.8462), gr_complex(0.3846, -0.6923),
   		gr_complex(0.3846, -0.5385), gr_complex(0.3846, -0.3846),
   		gr_complex(0.3846, -0.2308), gr_complex(0.3846, -0.0769),
   		gr_complex(0.3846, 1.1538), gr_complex(0.3846, 1.0000),
   		gr_complex(0.3846, 0.8462), gr_complex(0.3846, 0.6923),
   		gr_complex(0.3846, 0.5385), gr_complex(0.3846, 0.3846),
   		gr_complex(0.3846, 0.2308), gr_complex(0.3846, 0.0769),
   		gr_complex(0.2308, -1.1538), gr_complex(0.2308, -1.0000),
   		gr_complex(0.2308, -0.8462), gr_complex(0.2308, -0.6923),
   		gr_complex(0.2308, -0.5385), gr_complex(0.2308, -0.3846),
   		gr_complex(0.2308, -0.2308), gr_complex(0.2308, -0.0769),
   		gr_complex(0.2308, 1.1538), gr_complex(0.2308, 1.0000),
   		gr_complex(0.2308, 0.8462), gr_complex(0.2308, 0.6923),
   		gr_complex(0.2308, 0.5385), gr_complex(0.2308, 0.3846),
   		gr_complex(0.2308, 0.2308), gr_complex(0.2308, 0.0769),
   		gr_complex(0.0769, -1.1538), gr_complex(0.0769, -1.0000),
   		gr_complex(0.0769, -0.8462), gr_complex(0.0769, -0.6923),
   		gr_complex(0.0769, -0.5385), gr_complex(0.0769, -0.3846),
   		gr_complex(0.0769, -0.2308), gr_complex(0.0769, -0.0769),
   		gr_complex(0.0769, 1.1538), gr_complex(0.0769, 1.0000),
   		gr_complex(0.0769, 0.8462), gr_complex(0.0769, 0.6923),
   		gr_complex(0.0769, 0.5385), gr_complex(0.0769, 0.3846),
   		gr_complex(0.0769, 0.2308), gr_complex(0.0769, 0.0769)};


  } /* namespace ieee80211ah */
} /* namespace gr */

