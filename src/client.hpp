/*
    Copyright (c) 2007-2016 Contributors as noted in the AUTHORS file

    This file is part of libzmq, the ZeroMQ core engine in C++.

    libzmq is free software; you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    As a special exception, the Contributors give you permission to link
    this library with independent modules to produce an executable,
    regardless of the license terms of these independent modules, and to
    copy and distribute the resulting executable under terms of your choice,
    provided that you also meet, for each linked independent module, the
    terms and conditions of the license of that module. An independent
    module is a module which is not derived from or based on this library.
    If you modify this library, you must extend this exception to your
    version of the library.

    libzmq is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
    License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __ZMQ_CLIENT_HPP_INCLUDED__
#define __ZMQ_CLIENT_HPP_INCLUDED__

#include "socket_base.hpp"
#include "fq.hpp"
#include "lb.hpp"

namespace zmq
{
class ctx_t;
class msg_t;
class pipe_t;
class io_thread_t;

class client_t : public socket_base_t
{
  public:
    client_t (zmq::ctx_t *parent_, uint32_t tid_, int sid_);
    ~client_t ();

  protected:
    //  Overrides of functions from socket_base_t.
    void xattach_pipe (zmq::pipe_t *pipe_, bool subscribe_to_all_);
    int xsend (zmq::msg_t *msg_);
    int xrecv (zmq::msg_t *msg_);
    bool xhas_in ();
    bool xhas_out ();
    const blob_t &get_credential () const;
    void xread_activated (zmq::pipe_t *pipe_);
    void xwrite_activated (zmq::pipe_t *pipe_);
    void xpipe_terminated (zmq::pipe_t *pipe_);

  private:
    //  Messages are fair-queued from inbound pipes. And load-balanced to
    //  the outbound pipes.
    fq_t fq;
    lb_t lb;

    client_t (const client_t &);
    const client_t &operator= (const client_t &);
};
}

#endif
