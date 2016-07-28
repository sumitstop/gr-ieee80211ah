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
#include "ah_ofdm_decode_mac_impl.h"

namespace gr {
  namespace ieee80211ah {
  	  using namespace itpp;

    ah_ofdm_decode_mac::sptr
    ah_ofdm_decode_mac::make(bool log, bool debug)
    {
      return gnuradio::get_initial_sptr
        (new ah_ofdm_decode_mac_impl(log, debug));
    }

    /*
     * The private constructor
     */
    ah_ofdm_decode_mac_impl::ah_ofdm_decode_mac_impl(bool log, bool debug)
      : gr::block("ah_ofdm_decode_mac",
  			gr::io_signature::make(1, 1, 48 * sizeof(gr_complex)),
  			gr::io_signature::make(0, 0, 0)),
  			d_log(log),
  			d_debug(debug),
  			d_ofdm(BPSK_1_2),
  			d_tx(d_ofdm, 0),
  			d_frame_complete(true){
    	message_port_register_out(pmt::mp("out"));

    		// bpsk
    		int bpsk_bits[] = {0, 1};
    		bpsk.set(cvec(BPSK_D, 2), ivec(bpsk_bits, 2));

    		// qpsk
    		int qpsk_bits[] = {0, 1, 2, 3};
    		qpsk.set(cvec(QPSK_D, 4), ivec(qpsk_bits, 4));

    		// qam16
    		int qam16_bits[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    		qam16.set(cvec(QAM16_D, 16), ivec(qam16_bits, 16));

    		// qam64
    		int qam64_bits[] = {
    			 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
    			10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    			20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
    			30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
    			40, 41, 42, 43, 44, 45, 46, 47, 48, 49,
    			50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
    			60, 61, 62, 63};
    		qam64.set(cvec(QAM64_D, 64), ivec(qam64_bits, 64));

    		// qam256

    		int qam256_bits[] = {
    			 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
    			10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    			20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
    			30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
    			40, 41, 42, 43, 44, 45, 46, 47, 48, 49,
    			50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
    			60, 61, 62, 63, 64, 65, 66, 67, 68, 69,
    			70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
    			80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
    			90, 91, 92, 93, 94, 95, 96, 97, 98, 99,
    			100, 101, 102, 103, 104, 105, 106, 107, 108, 109,
    			110, 111, 112, 113, 114, 115, 116, 117, 118, 119,
    			120, 121, 122, 123, 124, 125, 126, 127, 128, 129,
    			130, 131, 132, 133, 134, 135, 136, 137, 138, 139,
    			140, 141, 142, 143, 144, 145, 146, 147, 148, 149,
    			150, 151, 152, 153, 154, 155, 156, 157, 158, 159,
    			160, 161, 162, 163, 164, 165, 166, 167, 168, 169,
    			170, 171, 172, 173, 174, 175, 176, 177, 178, 179,
    			180, 181, 182, 183, 184, 185, 186, 187, 188, 189,
    			190, 191, 192, 193, 194, 195, 196, 197, 198, 199,
    			200, 201, 202, 203, 204, 205, 206, 207, 208, 209,
    			210, 211, 212, 213, 214, 215, 216, 217, 218, 219,
    			220, 221, 222, 223, 224, 225, 226, 227, 228, 229,
    			230, 231, 232, 233, 234, 235, 236, 237, 238, 239,
    			240, 241, 242, 243, 244, 245, 246, 247, 248, 249,
    			250, 251, 252, 253, 254, 255};
    		qam64.set(cvec(QAM256_D, 256), ivec(qam256_bits, 256));
    }

    /*
     * Our virtual destructor.
     */
    ah_ofdm_decode_mac_impl::~ah_ofdm_decode_mac_impl()
    {
    }

    void
    ah_ofdm_decode_mac_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      /* <+forecast+> e.g. ninput_items_required[0] = noutput_items */
    }

    int
    ah_ofdm_decode_mac_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {

    	const gr_complex *in = (const gr_complex*)input_items[0];

    	int i = 0;

    	std::vector<gr::tag_t> tags;
    	const uint64_t nread = this->nitems_read(0);

    	dout << "Decode MAC: input " << ninput_items[0] << std::endl;

    	while(i < ninput_items[0]) {

    		get_tags_in_range(tags, 0, nread + i, nread + i + 1,
    			pmt::string_to_symbol("ofdm_start"));

    		if(tags.size()) {
    			if (d_frame_complete == false) {
    				dout << "Warning: starting to receive new frame before old frame was complete" << std::endl;
    				dout << "Already copied " << copied << " out of " << d_tx.n_sym << " symbols of last frame" << std::endl;
    			}
    			d_frame_complete = false;

    			pmt::pmt_t tuple = tags[0].value;
    			int len_data = pmt::to_uint64(pmt::car(tuple));
    			int encoding = pmt::to_uint64(pmt::cdr(tuple));

    			ofdm_param ofdm = ofdm_param((Encoding)encoding);
    			tx_param tx = tx_param(ofdm, len_data);

    			// sanity check, more than MAX_SYM may indicate garbage
    			if(tx.n_sym <= MAX_SYM && tx.n_encoded_bits <= MAX_BITS) {
    				d_ofdm = ofdm;
    				d_tx = tx;
    				copied = 0;
    				dout << "Decode MAC: frame start -- len " << len_data
    					<< "  symbols " << tx.n_sym << "  encoding "
    					<< encoding << std::endl;
    			} else {
    				dout << "Dropping frame which is too large (symbols or bits)" << std::endl;
    			}
    		}

    		if(copied < d_tx.n_sym) {
    			dout << "copy one symbol, copied " << copied << " out of " << d_tx.n_sym << std::endl;
    			std::memcpy(sym + (copied * 48), in, 48 * sizeof(gr_complex));
    			copied++;

    			if(copied == d_tx.n_sym) {
    				dout << "received complete frame - decoding" << std::endl;
    				decode();
    				in += 48;
    				i++;
    				d_frame_complete = true;
    				break;
    			}
    		}

    		in += 48;
    		i++;
    	}

    	consume(0, i);
    	return 0;
    }

    void ah_ofdm_decode_mac_impl::decode() {
    	demodulate();
    	deinterleave();
    	decode_conv();
    	descramble();
    	print_output();

    	// skip service field
    	boost::crc_32_type result;
    	result.process_bytes(out_bytes + 2, d_tx.psdu_size);
    	if(result.checksum() != 558161692) {
    		dout << "checksum wrong -- dropping" << std::endl;
    		return;
    	}

    	mylog(boost::format("encoding: %1% - length: %2% - symbols: %3%")
    			% d_ofdm.encoding % d_tx.psdu_size % d_tx.n_sym);

    	// create PDU
    	pmt::pmt_t blob = pmt::make_blob(out_bytes + 2, d_tx.psdu_size - 4);
    	pmt::pmt_t enc = pmt::from_uint64(d_ofdm.encoding);
    	pmt::pmt_t dict = pmt::make_dict();
    	dict = pmt::dict_add(dict, pmt::mp("encoding"), enc);
    	message_port_pub(pmt::mp("out"), pmt::cons(dict, blob));
    }

    void ah_ofdm_decode_mac_impl::demodulate() {

    	cvec symbols;
    	symbols.set_length(d_tx.n_sym * 48);
    	for(int i = 0; i < d_tx.n_sym * 48; i++) {
    		symbols[i] = std::complex<double>(sym[i]);
    	}

    	switch(d_ofdm.encoding) {
    	case BPSK_1_2:
    	//case BPSK_3_4:

    		bits = to_vec(bpsk.demodulate_bits(symbols));
    		break;

    	case QPSK_1_2:
    	case QPSK_3_4:

    		bits = to_vec(qpsk.demodulate_bits(symbols));
    		break;

    	case QAM16_1_2:
    	case QAM16_3_4:
    		bits = to_vec(qam16.demodulate_bits(symbols));
    		break;
    	case QAM64_2_3:
    	case QAM64_3_4:
    	case QAM64_5_6:
    		bits = to_vec(qam64.demodulate_bits(symbols));
    		break;

    	case QAM256_3_4:
    		bits = to_vec(qam256.demodulate_bits(symbols));
    		break;
    	}

    	// I hate the guy who wrote itpp
    	bits = bits * (-2) + 1;
    }

    void ah_ofdm_decode_mac_impl::deinterleave() {

    	int n_cbps = d_ofdm.n_cbps;
    	int first[n_cbps];
    	int second[n_cbps];
    	int s = std::max(d_ofdm.n_bpsc / 2, 1);

    	for(int j = 0; j < n_cbps; j++) {
    		first[j] = s * (j / s) + ((j + int(floor(16.0 * j / n_cbps))) % s);
    	}

    	for(int i = 0; i < n_cbps; i++) {
    		second[i] = 16 * i - (n_cbps - 1) * int(floor(16.0 * i / n_cbps));
    	}

    	for(int i = 0; i < d_tx.n_sym; i++) {
    		for(int k = 0; k < n_cbps; k++) {
    			deinter[i * n_cbps + second[first[k]]] = bits[i * n_cbps + k];
    		}
    	}
    }

    void ah_ofdm_decode_mac_impl::decode_conv() {
    	Punctured_Convolutional_Code code;
    	ivec generator(2);
    	generator(0)=0133;
    	generator(1)=0171;
    	code.set_generator_polynomials(generator, 7);

    	bmat puncture_matrix;
    	switch(d_ofdm.encoding) {
    	case BPSK_1_2:
    	case QPSK_1_2:
    	case QAM16_1_2:
    		puncture_matrix = "1 1; 1 1";
    		break;
    	//case BPSK_3_4:
    	case QPSK_3_4:
    	case QAM16_3_4:
    	case QAM64_3_4:
    	case QAM256_3_4:
    		puncture_matrix = "1 1 0; 1 0 1;";
    		break;
    	case QAM64_2_3:
    		puncture_matrix = "1 1 1 1 1 1; 1 0 1 0 1 0;";
    		break;
    	case QAM64_5_6:
    		puncture_matrix = "1 1 0 1 0; 1 0 1 0 1;";
    		break;
    	}
    	code.set_puncture_matrix(puncture_matrix);
    	code.set_truncation_length(30);

    	dout << "coding rate " << code.get_rate() << std::endl;
    	dout << d_tx.n_encoded_bits << std::endl;

    	vec rx_signal(deinter, d_tx.n_encoded_bits);

    	code.reset();
    	decoded_bits.set_length(d_tx.n_encoded_bits);
    	code.decode_tail(rx_signal, decoded_bits);

    	//dout << "length decoded " << decoded_bits.size() << std::endl;
    	//std::cout << decoded_bits << std::endl;
    }

    void ah_ofdm_decode_mac_impl::descramble () {
    	int state = 0;
    	for(int i = 0; i < 7; i++) {
    		if(decoded_bits(i)) {
    			state |= 1 << (6 - i);
    		}
    	}

    	int feedback;

    	for(int i = 7; i < decoded_bits.size(); i++) {
    		feedback = ((!!(state & 64))) ^ (!!(state & 8));
    		out_bits[i] = feedback ^ (int)decoded_bits(i);
    		state = ((state << 1) & 0x7e) | feedback;
    	}

    	for(int i = 0; i < decoded_bits.size(); i++) {
    		int bit = i % 8;
    		int byte = i / 8;
    		if(bit == 0) {
    			out_bytes[byte] = 0;
    		}

    		if(out_bits[i]) {
    			out_bytes[byte] |= (1 << bit);
    		}
    	}
    }

    void ah_ofdm_decode_mac_impl::print_output() {

    	dout << std::endl;
    	for(int i = 0; i < decoded_bits.size() / 8; i++) {
    		dout << std::setfill('0') << std::setw(2) << std::hex << ((unsigned int)out_bytes[i] & 0xFF) << std::dec << " ";
    		if(i % 16 == 15) {
    			dout << std::endl;
    		}
    	}
    	dout << std::endl;
    	for(int i = 0; i < decoded_bits.size() / 8; i++) {
    		if((out_bytes[i] > 31) && (out_bytes[i] < 127)) {
    			dout << ((char) out_bytes[i]);
    		} else {
    			dout << ".";
    		}
    	}
    	dout << std::endl;
    }

  } /* namespace ieee80211ah */
} /* namespace gr */

