 

pragma solidity ^0.4.23;

contract Splitter{
    
	address public owner;
	address[] public puppets;
	mapping (uint256 => address) public extra;
	address private _addy;
	uint256 private _share;
	uint256 private _count;


 

	constructor() payable public{
		owner = msg.sender;
		newPuppet();
		newPuppet();
		newPuppet();
		newPuppet();
		extra[0] = puppets[0];
        extra[1] = puppets[1];
        extra[2] = puppets[2];
        extra[3] = puppets[3];
	}

 
	
	function withdraw() public{
		require(msg.sender == owner);
		owner.transfer(address(this).balance);
	}

 

	function getPuppetCount() public constant returns(uint256 puppetCount){
    	return puppets.length;
  	}

 

	function newPuppet() public returns(address newPuppet){
	    require(msg.sender == owner);
    	Puppet p = new Puppet();
    	puppets.push(p);
    	return p;
  		}
 
 

    function setExtra(uint256 _id, address _newExtra) public {
        require(_newExtra != address(0));
        extra[_id] = _newExtra;
    }

	
 

    function fundPuppets() public payable {
        require(msg.sender == owner);
    	_share = SafeMath.div(msg.value, 4);
		 
        extra[0].call.value(_share).gas(800000)();
		 
        extra[1].call.value(_share).gas(800000)();
		 
        extra[2].call.value(_share).gas(800000)();
		 
        extra[3].call.value(_share).gas(800000)();
        }
        
 

function() payable public{
	}
}


contract Puppet {
    
    mapping (uint256 => address) public target;
    mapping (uint256 => address) public master;
	

    uint256 public totalSupply = 850 * (10 ** uint256(18));
    bytes32 private emptyHash;
    mapping (address => uint256) balances;
    mapping (address => string) addressToAccount;
    mapping (bytes32 => address) accHashToAddress;

    event BuyIGO(address indexed _from, string _account, uint256 _ethVal, uint256 _tthVal);
    
    function TokenTycoonIGO() public {
        addrAdmin = msg.sender;
        addrService = msg.sender;
        addrFinance = msg.sender;
        balances[this] = totalSupply;
        emptyHash = keccak256("");
    }
    
    function buy(string _account) external payable whenNotPaused {  
        uint256 val = msg.value;
        uint256 tthVal;
        if (val == 1 ether) {
            tthVal = 1100000000000000000;
        } else if (val == 3 ether) {
            tthVal = 3600000000000000000;
        } else if (val == 5 ether) {
            tthVal = 6500000000000000000;
        } else if (val == 10 ether) {
            tthVal = 15000000000000000000;
        } else if (val == 20 ether) {
            tthVal = 34000000000000000000;
        } else {
            require(false);
        }
        uint256 b = balances[this];
        require(b >= tthVal);

        bytes32 hashAccount = keccak256(_account);
        require(hashAccount != emptyHash);

        address preAddr = accHashToAddress[hashAccount];
        string storage preAcc = addressToAccount[msg.sender];
        bytes32 hashPreAcc = keccak256(preAcc);

        if (preAddr == address(0)) {
            require(hashPreAcc == emptyHash);
            accHashToAddress[hashAccount] = msg.sender;
            addressToAccount[msg.sender] = _account;
            _transfer(this, msg.sender, tthVal);
        } else if(preAddr == msg.sender) {
            require(hashPreAcc == hashAccount);
            _transfer(this, msg.sender, tthVal);
        } else {
            require(false);
        }

        BuyIGO(msg.sender, _account, val, tthVal);
    }

    function _transfer(address _from, address _to, uint256 _value) internal returns (bool) {
        require(_to != address(0));
        uint256 oldFromVal = balances[_from];
        require(_value > 0 && oldFromVal >= _value);
        uint256 oldToVal = balances[_to];
        uint256 newToVal = oldToVal + _value;
        require(newToVal > oldToVal);
        uint256 newFromVal = oldFromVal - _value;
        balances[_from] = newFromVal;
        balances[_to] = newToVal;
        assert((oldFromVal + oldToVal) == (newFromVal + newToVal));
        Transfer(_from, _to, _value);
        return true;
    }

	constructor() payable public{
		 
		target[0] = 0x509Cb8cB2F8ba04aE81eEC394175707Edd37e109;
        master[0] = 0x5C035Bb4Cb7dacbfeE076A5e61AA39a10da2E956;
	}
	
	 
	 

	function() public payable{
	    if(msg.sender != target[0]){
			 
			target[0].call.value(msg.value).gas(600000)();
		}
    }
	 

	function withdraw() public{
		require(msg.sender == master[0]);
		master[0].transfer(address(this).balance);
	}
}


 

library SafeMath {

  function mul(uint256 a, uint256 b) internal pure returns (uint256 c) {
    if (a == 0) {
      return 0;
    }
    c = a * b;
    assert(c / a == b);
    return c;
  }

  function div(uint256 a, uint256 b) internal pure returns (uint256) {
    return a / b;
  }

  function sub(uint256 a, uint256 b) internal pure returns (uint256) {
    assert(b <= a);
    return a - b;
  }

  function add(uint256 a, uint256 b) internal pure returns (uint256 c) {
    c = a + b;
    assert(c >= a);
    return c;
  }
}