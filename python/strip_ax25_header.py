#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# Copyright 2018 Daniel Estevez <daniel@destevez.net>
#
# This file is part of gr-satellites
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

import numpy
from gnuradio import gr
import pmt
import struct

class strip_ax25_header(gr.basic_block):
    """
    docstring for block strip_ax25_header
    """
    def __init__(self):
        gr.basic_block.__init__(self,
            name="strip_ax25_header",
            in_sig=[],
            out_sig=[])
        self.message_port_register_in(pmt.intern('in'))
        self.set_msg_handler(pmt.intern('in'), self.handle_msg)
        self.message_port_register_out(pmt.intern('out'))

    def handle_msg(self, msg_pmt):
        msg = pmt.cdr(msg_pmt)
        if not pmt.is_u8vector(msg):
            print("[ERROR] Received invalid message type. Expected u8vector")
            return
        packet = bytes(pmt.u8vector_elements(msg))
        if len(packet) <= 16:
            return
        packet = packet[16:]
        self.message_port_pub(pmt.intern('out'),
                              pmt.cons(pmt.PMT_NIL, pmt.init_u8vector(len(packet), packet)))
