

#include "NetManager.h"



/* ****************************************************************************
 * Constructors/Destructors
 */

/**
 * Initialize changeable values to defaults. Nothing special.
 */

TCPsocket sd, csd; /* Socket descriptor, Client socket descriptor */
IPaddress ip, *remoteIP;
int quit, quit2, len;
char buffer[512];

NetManager::NetManager()
{
  bool isServer = true;

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
}

void NetManager::receiveMessages()
{
  /* Wait for a connection, send data and term */
  quit = 0;
  while (!quit)
  {
    /* This check the sd if there is a pending connection.
    * If there is one, accept that, and open a new socket for communicating */
    if ((csd = SDLNet_TCP_Accept(sd)))
    {
      /* Now we can communicate with the client using csd socket
      * sd will remain opened waiting other connections */
 
      /* Get the remote address */
      if ((remoteIP = SDLNet_TCP_GetPeerAddress(csd)))
        /* Print the address, converting in the host format */
        printf("Host connected: %x %d\n", SDLNet_Read32(&remoteIP->host), SDLNet_Read16(&remoteIP->port));
      else
        fprintf(stderr, "SDLNet_TCP_GetPeerAddress: %s\n", SDLNet_GetError());
 
      quit2 = 0;
      while (!quit2)
      {
        if (SDLNet_TCP_Recv(csd, buffer, 512) > 0)
        {
          printf("Client say: %s\n", buffer);
 
          if(strcmp(buffer, "exit") == 0) /* Terminate this connection */
          {
            quit2 = 1;
            printf("Terminate connection\n");
          }
          if(strcmp(buffer, "quit") == 0) /* Quit the program */
          {
            quit2 = 1;
            quit = 1;
            printf("Quit program\n");
          }
        }
      }
 
      /* Close the client socket */
      SDLNet_TCP_Close(csd);
    }
  }
}

void NetManager::setupClient()
{
  /* Resolve the host we are connecting to */
  if (SDLNet_ResolveHost(&ip, "assassin-bug.cs.utexas.edu", 2000) < 0)
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
}

void NetManager::sendMessages()
{
  /* Send messages */
  quit = 0;
  strcpy(buffer, "quit");
  while (!quit)
  {
    len = strlen(buffer) + 1;
    if (SDLNet_TCP_Send(sd, (void *)buffer, len) < len)
    {
      fprintf(stderr, "SDLNet_TCP_Send: %s\n", SDLNet_GetError());
      exit(EXIT_FAILURE);
    }
 
    if(strcmp(buffer, "exit") == 0)
      quit = 1;
    if(strcmp(buffer, "quit") == 0)
      quit = 1;
  }
}


