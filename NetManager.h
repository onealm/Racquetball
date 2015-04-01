

#ifndef NETMANAGER_H_
#define NETMANAGER_H_

#include "SDL/SDL_net.h"

class NetManager 
{
  public:
    NetManager(void);
    virtual ~NetManager(void);

    void receiveMessages(void);
    void sendMessages(void);

  protected:
    void setupServer(void);
    void setupClient(void);

};

#endif /* NETMANAGER_H_ */
