#pragma once

#include <vector>
#include <unordered_map>
#include "Common.h"
#include "Room.h"

class ITcpNetwork;
class ILog;

using ERROR_CODE = Common::ERROR_CODE;
using TcpNet = ITcpNetwork;

class User;

struct LobbyUser
{
	short Index = 0;
	User* pUser = nullptr;
};

class Lobby
{
public:
	Lobby() {};
	virtual ~Lobby() {};

	void Init(const short lobbyIndex, const short maxLobbyUserCount, const short maxRoomCountByLobby, const short maxRoomUserCount);

	void SetNetwork(TcpNet* pNetwork, ILog* pLogger);

	short GetIndex() { return m_LobbyIndex; }


	ERROR_CODE EnterUser(User* pUser);
	ERROR_CODE LeaveUser(const int userIndex);

	short GetUserCount();


	void NotifyLobbyEnterUserInfo(User* pUser);
	void NotifyLobbyLeaveUserInfo(User* pUser);
	void NotifyChat(const int sessionIndex, const char* pszUserID, const wchar_t* pszMsg);
	void NotifyWhisper(const int sessionIndex, const char* pszUserID, const char* targetUserID, const wchar_t* pszMsg);

	ERROR_CODE SendRoomList(const int sessionId, const short startRoomId);
	ERROR_CODE SendUserList(const int sessionId, const short startUserIndex);
	
	Room* GetRoom(const short roomIndex);

	void NotifyChangedRoomInfo(const short roomIndex);

	auto MaxUserCount() { return (short)m_MaxUserCount; }
	auto MaxRoomCount() { return (short)m_RoomList.size(); }

protected:
	void SendToAllUser(const short packetId, const short dataSize, char* pData, const int passUserindex = -1);
	void SendToTargetUser(const short packetId, const short dataSize, char* pData, const int targetUserIndex);

protected:
	User* FindUser(const int userIndex);
	ERROR_CODE AddUser(User* pUser);
	void RemoveUser(const int userIndex);


protected:
	ILog* m_pRefLogger;
	TcpNet* m_pRefNetwork;


	short m_LobbyIndex = 0;

	short m_MaxUserCount = 0;
	std::vector<LobbyUser> m_UserList;
	std::unordered_map<int, User*> m_UserIndexDic;
	std::unordered_map<std::string, User*> m_UserIDDic;

	std::vector<Room> m_RoomList;
};
