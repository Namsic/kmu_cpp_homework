pragma solidity ^0.4.24;

contract AutomaticWithdrawal {
    struct UserInfo {
        uint balance;
        uint baseTime;
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
    
    modifier onlyOwner {
        require(msg.sender == owner);
        _;
    }
    modifier renewBalance() {
        // sender 잔액 갱신, 이용요금 차감
        require(msg.sender != owner);
        
        address _addr = msg.sender;
        uint usageTime = (now - userMap[_addr].baseTime);
        uint n = usageTime / term;
        uint curCharge = n * charge;
        
        // 이용가능 시간이 남은 경우
        if(userMap[_addr].balance >= curCharge) {
            owner.transfer(curCharge);
            userMap[_addr].balance -= curCharge;
            userMap[_addr].baseTime -= n * term;
        }
        // 지불한 요금을 모두 사용한 경우
        else {
            owner.transfer(curCharge);
            delete userMap[_addr];
        }
        _;
    }
    
    function getOwner() public view returns (address) {
        return owner;
    }
    
    function getCharge() public view returns (uint) {
        return charge;
    }
    
    function getTerm() public view returns (uint) {
        return term;
    }
    
    function payment() public payable {
        // user의 요금 충전
        userMap[msg.sender].balance += msg.value;
        
        if(userMap[msg.sender].baseTime == 0) {
            // 이용 시작 시 첫 요금 차감 및 시간 설정
            require(msg.value >= charge);
            userMap[msg.sender].balance -= charge;
            userMap[msg.sender].baseTime = now;
        }
    }
    
    function getBalance() public renewBalance returns (uint) {
        // sender의 현재 잔액 확인
        return userMap[msg.sender].balance;
    }
    
    function returnBalance() public renewBalance {
        // sender의 잔액 반환
        msg.sender.transfer(userMap[msg.sender].balance);
        delete userMap[msg.sender];
    }
    
    function useService() public renewBalance returns (bool) {
        // 제공되는 service의 사용 가능 여부
        return userMap[msg.sender].balance > 0;
    }
    
    function destroy() public onlyOwner {
        selfdestruct(owner);
    }
}