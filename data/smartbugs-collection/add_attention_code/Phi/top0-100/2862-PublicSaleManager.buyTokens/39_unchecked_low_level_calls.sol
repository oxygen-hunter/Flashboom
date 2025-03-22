 

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
contract ERC20 {
    function balanceOf(address tokenOwner) public constant returns (uint256 balance);
    function transfer(address to, uint256 tokens) public returns (bool success);
}

contract owned {
    function owned() public { owner = msg.sender; }
    address owner;

    modifier onlyOwner {
        require(msg.sender == owner);
        _;
    }
}

contract PublicSaleManager is owned {

    mapping (address => bool) _earlyList;
    mapping (address => bool) _whiteList;
    mapping (address => uint256) _bonus;
    mapping (address => uint256) _contributedETH;

    address _tokenAddress = 0xAF815e887b039Fc06a8ddDcC7Ec4f57757616Cd2;
    uint256 _conversionRate = 0;
    uint256 _startTime = 0;

    uint256 _totalSold = 0;
    uint256 _totalBonus = 0;

    uint256 _regularPersonalCap = 1e20; // 100 ETH
    uint256 _higherPersonalCap = 2e20; // 200 ETH
    uint256 _minimumAmount = 2e17; // 0.2 ETH

    bool _is_stopped = false;

    function buyTokens() payable public {
        require(_is_stopped == false);

        // Validates whitelist.
        require(_whiteList[msg.sender] == true || _earlyList[msg.sender] == true);

        if (_earlyList[msg.sender]) {
            require(msg.value + _contributedETH[msg.sender] <= _higherPersonalCap);
        } else {
            require(msg.value + _contributedETH[msg.sender] <= _regularPersonalCap);
        }

        require(msg.value >= _minimumAmount);

        // Validates time.
        require(now > _startTime);
        require(now < _startTime + (31 days));

        // Calculates the purchase amount.
        uint256 purchaseAmount = msg.value * _conversionRate;
        require(_conversionRate > 0 && purchaseAmount / _conversionRate == msg.value);

        // Calculates the bonus amount.
        uint256 bonus = 0;
        if (_totalSold + purchaseAmount < 5e26) {
            // 10% bonus for the first 500 million OGT.
            bonus = purchaseAmount / 10;
        } else if (_totalSold + purchaseAmount < 10e26) {
            // 5% bonus for the first 1 billion OGT.
            bonus = purchaseAmount / 20;
        }

        // Checks that we still have enough balance.
        require(ERC20(_tokenAddress).balanceOf(this) >= _totalBonus + purchaseAmount + bonus);

        // Transfers the non-bonus part.
        ERC20(_tokenAddress).transfer(msg.sender, purchaseAmount);
        _contributedETH[msg.sender] += msg.value;

        // Records the bonus.
        _bonus[msg.sender] += bonus;

        _totalBonus += bonus;
        _totalSold += (purchaseAmount + bonus);
    }
}
