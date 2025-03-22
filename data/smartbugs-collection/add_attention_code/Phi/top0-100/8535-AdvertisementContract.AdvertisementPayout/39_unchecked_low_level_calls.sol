 

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
library SafeMath {
  function mul(uint a, uint b) internal pure returns (uint) {
    uint c = a * b;
    assert(a == 0 || c / a == b);
    return c;
  }

  function div(uint a, uint b) internal pure returns (uint) {
    uint c = a / b;
    return c;
  }

  function sub(uint a, uint b) internal pure returns (uint) {
    assert(b <= a);
    return a - b;
  }

  function add(uint a, uint b) internal pure returns (uint) {
    uint c = a + b;
    assert(c >= a);
    return c;
  }
}

contract ERC20Interface {
  function balanceOf(address tokenOwner) public constant returns (uint balance);
  function mint(address from, address to, uint tokens) public;
}

contract AdvertisementContract {
  using SafeMath for uint256;

  struct Advertisement {
    address advertiser;
    uint advertisementId;
    uint amountToBePaid;
    bool isUnlocked;
  }

  struct Voter {
    address publicKey;
    uint amountEarned;
  }

  struct VoteAdvertisementPayoutScheme {
    uint voterPercentage;
    uint systemPercentage;
  }

  ERC20Interface public token;
  VoteAdvertisementPayoutScheme voteAdvertismentPayoutSchemeObj;
  mapping (uint => Voter[]) advertisementVoterList;
  mapping (uint => Advertisement) advertisementList;
  uint localIntAsPerNeed;
  Voter[] voters;
  address public wallet;

  constructor(address _wallet, address _tokenAddress) public {
    wallet = _wallet;
    token = ERC20Interface(_tokenAddress);
    setup();
  }

  function setup() internal {
    voteAdvertismentPayoutSchemeObj = VoteAdvertisementPayoutScheme({voterPercentage: 79, systemPercentage: 21});
  }

  function AdvertisementPayout (uint advId) public {
    require(msg.sender == wallet);
    require(token.balanceOf(wallet) >= advertisementList[advId].amountToBePaid);
    require(advertisementList[advId].advertisementId == advId);
    require(advertisementList[advId].isUnlocked == true);
    require(advertisementList[advId].amountToBePaid > 0);

    uint j = 0;

    voters = advertisementVoterList[advertisementList[advId].advertisementId];
    localIntAsPerNeed = voteAdvertismentPayoutSchemeObj.voterPercentage;
    uint voterPayout = advertisementList[advId].amountToBePaid.mul(localIntAsPerNeed).div(100);
    uint perVoterPayout = voterPayout.div(voters.length);

    localIntAsPerNeed = voteAdvertismentPayoutSchemeObj.systemPercentage;
    uint systemPayout = advertisementList[advId].amountToBePaid.mul(localIntAsPerNeed).div(100);

    for (j = 0; j < voters.length; j++) {
      token.mint(wallet, voters[j].publicKey, perVoterPayout);
      voters[j].amountEarned = voters[j].amountEarned.add(perVoterPayout);
      advertisementList[advId].amountToBePaid = advertisementList[advId].amountToBePaid.sub(perVoterPayout);
    }

    advertisementList[advId].amountToBePaid = advertisementList[advId].amountToBePaid.sub(systemPayout);
    require(advertisementList[advId].amountToBePaid == 0);
  }
}
