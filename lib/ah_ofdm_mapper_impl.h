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

#ifndef INCLUDED_IEEE80211AH_AH_OFDM_MAPPER_IMPL_H
#define INCLUDED_IEEE80211AH_AH_OFDM_MAPPER_IMPL_H

#include <ieee80211ah/ah_ofdm_mapper.h>
#include "utils_ah.h"

namespace gr {
  namespace ieee80211ah {

    class ah_ofdm_mapper_impl : public ah_ofdm_mapper
    {
     private:
      // Nothing to declare in this block.

     public:
      ah_ofdm_mapper_impl(Encoding e, bool debug);
      ~ah_ofdm_mapper_impl();

      // Where all the action really happens
      void forecast (int noutput_items, gr_vector_int &ninput_items_required);

      int general_work(int noutput_items,
           gr_vector_int &ninput_items,
           gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);

     void print_message(const char *msg, size_t len);

     void set_encoding_ah(Encoding encoding);

     private:
      // Nothing to declare in this block.
     bool         d_debug;
     char*        d_symbols;
     int          d_symbols_offset;
     int          d_symbols_len;
     ofdm_param   d_ofdm;
     gr::thread::mutex d_mutex;
    };

  } // namespace ieee80211ah
} // namespace gr

#endif /* INCLUDED_IEEE80211AH_AH_OFDM_MAPPER_IMPL_H */

