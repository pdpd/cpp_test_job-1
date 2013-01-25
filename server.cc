#include "common.h"
#include "ace/Reactor.h"

ACE_Reactor * reactor;

#include "acceptor.h"


int main()
{
    ACE_NEW_RETURN(reactor,ACE_Reactor,1);
    ACE_INET_Addr addr(PORT);

    Logging_Acceptor *peer_acceptor;

    ACE_NEW_RETURN(peer_acceptor, Logging_Acceptor,2);

    if (peer_acceptor->open(addr,reactor)==-1)
    {
        ACE_ERROR_RETURN((LM_ERROR,"Opening Acceptor\n"),-1);
    }
    for (;;)
        reactor->handle_events();
}

