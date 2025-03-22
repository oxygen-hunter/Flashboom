 

pragma solidity ^0.4.23;        

 
 
 
 
 
 
 
 
 
 
 
 
   
contract Delta {     

	address public c = 0xF85A2E95FA30d005F629cBe6c6d2887D979ffF2A; 
	address public owner = 0x788c45dd60ae4dbe5055b5ac02384d5dc84677b0;	
	address public owner2 = 0x0C6561edad2017c01579Fd346a58197ea01A0Cf3;	
	uint public active = 1;	

	uint public token_price = 10**18*1/1000; 	

	 
	function() payable {        
	    tokens_buy();        
	}

	 
    function tokens_buy() payable returns (bool) {         
        
        require(active > 0);
        require(msg.value >= token_price);        

        uint tokens_buy = msg.value*10**18/token_price;

        require(tokens_buy > 0);

        if(!c.call(bytes4(sha3("transferFrom(address,address,uint256)")),owner, msg.sender,tokens_buy)){
        	return false;
        }

        uint sum2 = msg.value * 3 / 10;           
         
        owner2.send(sum2);

        return true;
      }     

       
      function withdraw(uint256 _amount) onlyOwner returns (bool result) {
          uint256 balance;
          balance = this.balance;
          if(_amount > 0) balance = _amount;
           
          owner.send(balance);
          return true;
      }

       
      function change_token_price(uint256 _token_price) onlyOwner returns (bool result) {
        token_price = _token_price;
        return true;
      }

       
      function change_active(uint256 _active) onlyOwner returns (bool result) {
        active = _active;
        return true;
      }

       
    	modifier onlyOwner() {
        if (msg.sender != owner) {
            throw;
        }
        _;
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
