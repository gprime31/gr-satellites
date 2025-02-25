/* -*- c++ -*- */
/*
 * Copyright 2022 Daniel Estevez <daniel@destevez.net>.
 *
 * This file is part of gr-satellites
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_SATELLITES_DOPPLER_CORRECTION_H
#define INCLUDED_SATELLITES_DOPPLER_CORRECTION_H

#include <gnuradio/sync_block.h>
#include <satellites/api.h>

namespace gr {
namespace satellites {

/*!
 * \brief Performs Doppler correction using a frequency vs. time file
 * \ingroup satellites
 *
 * \details
 * The Doppler Correction block uses a text file listing frequency vs. time to
 * perform Doppler correction on its input signal. The same block can be used
 * for Doppler simulation by inverting the frequency values in the input file or
 * by taking the complex conjugate of the output of the block.
 *
 * The text file should contain lines with a timestamp and a frequency separated
 * by a space. The timestamps are given in seconds, and typically consist of
 * UNIX time. The t0 parameter in the block constructor gives the starting time,
 * which is the timestamp corresponding to the first sample processed by the
 * block. As long as the timestamps in the file and this timestamp are
 * consistent, the block will work correctly. The frequencies are given in Hz.
 *
 * The block can also use time tags such as those generated by the UHD Source
 * block to update its internal timestamp. In this case the timestamps in the
 * file should use UNIX seconds, since the UHD timestamps also use UNIX
 * seconds. When using UHD time tags, the t0 parameter can be left as 0.
 *
 * The Doppler correction block interpolates the frequency linearly between each
 * pair of entries in the text file, and generates a correction with continuous
 * phase.
 */
class SATELLITES_API doppler_correction : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<doppler_correction> sptr;

    /*!
     * \brief Build the Doppler Correction block.
     *
     * \param filename Path of the text file describing the Doppler data
     * \param samp_rate Sample rate
     * \param t0 Timestamp corresponding to the first sample
     */
    static sptr make(std::string& filename, double samp_rate, double t0);
};

} // namespace satellites
} // namespace gr

#endif /* INCLUDED_SATELLITES_DOPPLER_CORRECTION_H */
