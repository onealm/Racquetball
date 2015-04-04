

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

TCPsocket sd, csd; /* Socket descriptor, Client socket descriptor */
IPaddress ip, *remoteIP;
int quit, quit2, len;
const int kBufferSize = 1024; // 1024 bytes
uint32_t buffer[8];
bool isOpen, isOpen2;


const char* hostName = "jelly-belly.cs.utexas.edu";



NetManager::NetManager()
{
  //bool isServer = true;

  isOpen = false;

  if (SDLNet_Init() < 0)
  {
    printf("SDLNet_Init FAILED\n");
    exit(0);
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

bool NetManager::isConnected()
{
  if(csd && sd)
  {
    return true;
  }
  return false;
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

  // printf("Server setup!!!\n\n\n\n\n\n");
}

void NetManager::setupClient()
{
  /* Resolve the host we are connecting to */
  //if (SDLNet_ResolveHost(&ip, "peanut-head-bug.cs.utexas.edu", 2000) < 0)
  if (SDLNet_ResolveHost(&ip, hostName, 2000) < 0)
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
  // printf("Client connected to server!!!\n\n\n\n");
}


void NetManager::receiveClientMessages()
{
  /* Wait for a connection, send data and term */
  len = sizeof(buffer);

  int num_recvd = 0;
  int total_recvd = 0;
  int num_attempts = 0;
  const int kMaxAttempts = 10000000;
  uint32_t* dest = reinterpret_cast<uint32_t*>(&buffer[0]);

  /* This checks the sd if there is a pending connection.
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

  int recLength = len;

  // while (total_recvd < recLength && num_attempts < kMaxAttempts)
  // {
    if ((num_recvd = SDLNet_TCP_Recv(csd, (void *) dest, recLength - total_recvd)) > 0)
    {
      // printf("****num_recvd: %d\n", num_recvd);
      total_recvd += num_recvd;
      dest += num_recvd;
    }
    ++num_attempts;
  // }

  // printf("Received %d of %d on %d out of %d attempts.\n",
  //   total_recvd, len, num_attempts, kMaxAttempts);
  // for (int i = 0; i < len / sizeof(float); ++i) 
  // {
  //    printf("Recv**************buffer[%d] = %lu\n", i, buffer[i]);
  // }
}

void NetManager::receiveServerMessages()
{
  // printf("GOT TO RECEIVE\n");
  /* Wait for a connection, send data and term */
  len = sizeof(buffer);

  int num_recvd = 0;
  int total_recvd = 0;
  int num_attempts = 0;
  const int kMaxAttempts = 10000000;
  uint32_t* dest = reinterpret_cast<uint32_t*>(&buffer[0]);


  int recLength = len;

  // while (total_recvd < recLength && num_attempts < kMaxAttempts)
  // {
    if ((num_recvd = SDLNet_TCP_Recv(sd, (void *) dest, recLength - total_recvd)) > 0)
    {
      // printf("****num_recvd: %d\n", num_recvd);
      total_recvd += num_recvd;
      dest += num_recvd;
    }
  // }
  // for (int i = 0; i < len / sizeof(float); ++i) 
  // {
  //    printf("Recv**************buffer[%d] = %lu\n", i, buffer[i]);
  // }
}

void NetManager::sendClientMessages(uint32_t *sendBuffer)
{
  /* Send messages */
  quit = 0;
  int bytesSent = 0;
  len = 32;
   
  // printf("len is %d\n", len);

  for (int i = 0; i < len/sizeof(uint32_t); i++)
  {
    // printf("Send: buffer[%d] is %lu\n", i, sendBuffer[i]);
  }

  //printf("buffer0 is %f\n\n\n\n\n\n", buffer[0]);
  bytesSent = SDLNet_TCP_Send(sd, (void *)sendBuffer, len);
  // printf("***bytesSent: %d\n", bytesSent);
  if (bytesSent < len)
  {
    // fprintf(stderr, "SDLNet_TCP_Send: %s\n", SDLNet_GetError()); 
    exit(EXIT_FAILURE);
  }
}

void NetManager::sendServerMessages(uint32_t *sendBuffer)
{
  /* Send messages */
  quit = 0;
  int bytesSent = 0;
  len = 32;
   
  // printf("len is %d\n", len);

  for (int i = 0; i < len/sizeof(uint32_t); i++)
  {
    // printf("Send: buffer[%d] is %lu\n", i, sendBuffer[i]);
  }

  //printf("buffer0 is %f\n\n\n\n\n\n", buffer[0]);
  bytesSent = SDLNet_TCP_Send(csd, (void *)sendBuffer, len);
  // printf("***bytesSent: %d\n", bytesSent);
  if (bytesSent < len)
  {
    // fprintf(stderr, "SDLNet_TCP_Send: %s\n", SDLNet_GetError()); 
    exit(EXIT_FAILURE);
  }
}

uint32_t* NetManager::getBuffer(void)
{
  return buffer;
}
