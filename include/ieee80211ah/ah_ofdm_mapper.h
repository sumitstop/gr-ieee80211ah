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


#ifndef INCLUDED_IEEE80211AH_AH_OFDM_MAPPER_H
#define INCLUDED_IEEE80211AH_AH_OFDM_MAPPER_H

#include <ieee80211ah/api.h>
#include <gnuradio/block.h>


enum Encoding {
	  BPSK_1_2  = 0,
	  QPSK_1_2  = 1,
	  QPSK_3_4  = 2,
	  QAM16_1_2 = 3,
	  QAM16_3_4 = 4,
	  QAM64_2_3 = 5,
	  QAM64_3_4 = 6,
	  QAM64_5_6 = 7,
	  QAM256_3_4 = 8,
 };

namespace gr {
  namespace ieee80211ah {

    /*!
     * \brief <+description of block+>
     * \ingroup ieee80211ah
     *
     */
    class IEEE80211AH_API ah_ofdm_mapper : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<ah_ofdm_mapper> sptr;

      static sptr make(Encoding mcs, bool debug = false);
      virtual void set_encoding_ah(Encoding encoding) = 0;
    };

  } // namespace ieee80211ah
} // namespace gr

#endif /* INCLUDED_IEEE80211AH_AH_OFDM_MAPPER_H */
