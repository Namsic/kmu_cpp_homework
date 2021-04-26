pragma solidity ^0.4.24;

contract AutomaticWithdrawal {
    struct UserInfo {
        uint balance;
        uint startTime;
    }
    address owner;  // contract 소유자
    uint charge;    // 결제될 요금
    uint term;      // 한 번 결제 시 사용가능 기간
    
    mapping (address => UserInfo) userMap;  // 각 이용자의 정보
    
    constructor (uint _charge, uint _term) public {
        owner = msg.sender;
        charge = _charge;
        term = _term;
    }
    
    function payment() public payable {
        userMap[msg.sender].balance += msg.value - charge;
        
        if(userMap[msg.sender].startTime == 0) {
            require(msg.value >= charge);
            userMap[msg.sender].balance -= charge;
            userMap[msg.sender].startTime = now;
        }
    }
    
    function getBalance() public returns (uint){
        renewBalance(msg.sender);
        return userMap[msg.sender].balance;
    }
    
    function returnBalance() public {
        renewBalance(msg.sender);
        msg.sender.transfer(userMap[msg.sender].balance);
        userMap[msg.sender].balance = 0;
        userMap[msg.sender].startTime = 0;
    }

    function renewBalance(address _addr) private {
        uint numCharge = (now - userMap[_addr].startTime) / term;
        uint curCharge = numCharge * charge;
        if(userMap[_addr].balance >= curCharge) {
            owner.transfer(curCharge);
            userMap[_addr].balance -= curCharge;
        }
        else {
            owner.transfer(userMap[_addr].balance);
            userMap[_addr].balance = 0;
            userMap[_addr].startTime = 0;
        }
    }
    
    function useService() public returns (string) {
        renewBalance(msg.sender);
        if(userMap[msg.sender].balance > 0) {
            return "ok";
        }
        else {
            return "fail";
        }
    }
}