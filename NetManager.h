

#ifndef NETMANAGER_H_
#define NETMANAGER_H_

#include "SDL/SDL_net.h"

class NetManager 
{
  public:
    NetManager(void);
    virtual ~NetManager(void);

    //Setup
    void setupServer(void);
    void setupClient(void);

    bool isConnected(void);

    //Receive
    void receiveClientMessages(void);
    void receiveServerMessages(void);

    //Send
    void sendServerMessages(uint32_t *buffer);
    void sendClientMessages(uint32_t *buffer);
    

};

#endif /* NETMANAGER_H_ */
