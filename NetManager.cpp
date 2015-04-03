

#include "NetManager.h"
#include "BaseApplication.h"
#include "PlayingRoom.h"
#include "Player.h"
#include "Ball.h"



/* ****************************************************************************
 * Constructors/Destructors
 */

/**
 * Initialize changeable values to defaults. Nothing special.
 */

TCPsocket sd, csd, csdTemp; /* Socket descriptor, Client socket descriptor */
IPaddress ip, *remoteIP;
int quit, quit2, len;
const int kBufferSize = 1024; // 1024 bytes
uint8_t buffer[kBufferSize];
int bytesSent;
bool isOpen;

NetManager::NetManager()
{
  bool isServer = true;
  ;
  isOpen = false;

  if (SDLNet_Init() < 0)
  {
    printf("SDLNet_Init FAILED\n");
    exit(0);
  }

  if(isServer)
  {
    setupServer();
    //receiveMessages();
  }
  else
  {
    setupClient();
    //sendMessages();
  }


}

/**
 * Standard destruction. Calls close().
 */
NetManager::~NetManager() 
{
  /* Close the client socket */
  SDLNet_TCP_Close(csd);

  SDLNet_Quit();
}

void NetManager::setupServer()
{

  /* Resolving the host using NULL make network interface to listen */
  if (SDLNet_ResolveHost(&ip, NULL, 2000) < 0)
  {
    printf("SDLNet_ResolveHost FAILED\n");
    exit(0);
  }

  /* Open a connection with the IP provided (listen on the host's port) */
  if (!(sd = SDLNet_TCP_Open(&ip)))
  {
    printf("SDLNet_TCP_Open FAILED\n");
    exit(0);
  }
  printf("Server setup!!!\n\n\n\n\n\n");
}


void NetManager::receiveMessages()
{
  /* Wait for a connection, send data and term */
  // quit = 0;
  // while (!quit)
  // {
    len = sizeof(buffer);
    printf("len = %d\n", len);

    int num_recvd = 0;
    int total_recvd = 0;
    int num_attempts = 0;
    const int kMaxAttempts = 10000000;
    uint8_t* dest = reinterpret_cast<uint8_t*>(&buffer[0]);
    /* This check the sd if there is a pending connection.
    * If there is one, accept that, and open a new socket for communicating */

    if (!isOpen) 
    {
      if (!(csd = SDLNet_TCP_Accept(sd))) 
      {
        printf("Couldn't accept client connection.\n");
        return;
      }
      isOpen = true;
    }
      /* Now we can communicate with the client using csd socket
      * sd will remain opened waiting other connections */
      /* Get the remote address */
      if ((remoteIP = SDLNet_TCP_GetPeerAddress(csd)))
        printf("Host connected: %x %d\n", SDLNet_Read32(&remoteIP->host), SDLNet_Read16(&remoteIP->port));
      else
        fprintf(stderr, "SDLNet_TCP_GetPeerAddress: %s\n", SDLNet_GetError());
 
      while (total_recvd < len && num_attempts < kMaxAttempts)
      {
        if ((num_recvd = SDLNet_TCP_Recv(csd, (void *) dest, len - total_recvd)) > 0)
        {
          // printf("Client say: %s\n", buffer);
 
          // if(strcmp(buffer, "exit") == 0) /* Terminate this connection */
          // {
          //   quit2 = 1;
          //   printf("Terminate connection\n");
          // }
          // if(strcmp(buffer, "quit") == 0) /* Quit the program */
          // {
          //quit2 = 1;
          //quit = 1;
          //   printf("Quit program\n");
          // }
          total_recvd += num_recvd;
          dest += num_recvd;
        }
        ++num_attempts;
      // }
      }
      /* Close the client socket */
      ///SDLNet_TCP_Close(csd);
    
    printf("Received %d of %d on %d out of %d attempts.\n",
      total_recvd, len, num_attempts, kMaxAttempts);
    for (int i = 0; i < len / sizeof(float); ++i) 
    {
       printf("**************buffer[%d] = %lu\n", i, buffer[i]);
    }
  // }
}

void NetManager::setupClient()
{
  /* Resolve the host we are connecting to */
  //if (SDLNet_ResolveHost(&ip, "peanut-head-bug.cs.utexas.edu", 2000) < 0)
  if (SDLNet_ResolveHost(&ip, "localhost", 2000) < 0)
  {
    printf("SDLNet_ResolveHost FAILED\n");
    exit(0);
  }
 
  /* Open a connection with the IP provided (listen on the host's port) */
  if (!(sd = SDLNet_TCP_Open(&ip)))
  {
    printf("SDLNet_TCP_Open FAILED \n");
    exit(0);
  }
  printf("Client connected to server!!!\n\n\n\n");
}

void NetManager::sendMessages(uint32_t *buffer)
{
  /* Send messages */
  quit = 0;
  bytesSent = 0;
  len = sizeof(buffer);
 // int num_attempts = 0;
 // const int kMaxAttempts = 1000;
//  while (bytesSent < len && num_attempts < kMaxAttempts)
//  {
   
    printf("len is %d\n", len);
    // uint32_t timestamp = time(NULL);
    // int i;
    // for (i = 0; i < 7; i++)
    // {
    //   buffer[i] = timestamp;
    //   ++timestamp;
    // }
    for (int i = 0; i < len; i++)
    {
      printf("buffer[%d] is %lu\n", i, buffer[i]);
    }
 
    //printf("buffer0 is %f\n\n\n\n\n\n", buffer[0]);
    bytesSent += SDLNet_TCP_Send(sd, (void *)buffer, len);
    if (bytesSent < len)
    {
      fprintf(stderr, "SDLNet_TCP_Send: %s\n", SDLNet_GetError()); 
      exit(EXIT_FAILURE);
    }
  
    //++num_attempts;
    // if(strcmp(buffer, "exit") == 0)
    //   quit = 1;
    // if(strcmp(buffer, "quit") == 0)
  //}
}


