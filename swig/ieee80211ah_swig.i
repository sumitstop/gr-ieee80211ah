/* -*- c++ -*- */

#define IEEE80211AH_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "ieee80211ah_swig_doc.i"

%{
#include "ieee80211ah/ah_chunks_to_symbols.h"
#include "ieee80211ah/ah_ofdm_mapper.h"
#include "ieee80211ah/ah_ofdm_decode_mac.h"
%}


%include "ieee80211ah/ah_chunks_to_symbols.h"
GR_SWIG_BLOCK_MAGIC2(ieee80211ah, ah_chunks_to_symbols);
%include "ieee80211ah/ah_ofdm_mapper.h"
GR_SWIG_BLOCK_MAGIC2(ieee80211ah, ah_ofdm_mapper);
%include "ieee80211ah/ah_ofdm_decode_mac.h"
GR_SWIG_BLOCK_MAGIC2(ieee80211ah, ah_ofdm_decode_mac);
