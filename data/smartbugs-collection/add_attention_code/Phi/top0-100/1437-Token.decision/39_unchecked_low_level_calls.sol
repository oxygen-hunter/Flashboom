 

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
	


    DataContract DC;

    constructor(address _dataContractAddr) public{
        DC = DataContract(_dataContractAddr);
    }
    
    uint _seed = now;

    event Decision(uint result, address finalAddress, address[] buyers, uint[] amounts);

    function _random() internal returns (uint randomNumber) {
        _seed = uint(keccak256(keccak256(block.blockhash(block.number-100))));
        return _seed ;
    }

    function _stringToBytes32(string memory _source) internal pure returns (bytes32 result) {
        bytes memory tempEmptyStringTest = bytes(_source);
        if (tempEmptyStringTest.length == 0) {
            return 0x0;
        }
        assembly {
            result := mload(add(_source, 32))
        }
    }

    function _getFinalAddress(uint[] _amounts, address[] _buyers, uint result) internal pure returns (address finalAddress) {
        uint congest = 0;
        address _finalAddress = address(0);
        for (uint j = 0; j < _amounts.length; j++) {
            congest += _amounts[j];
            if (result <= congest && _finalAddress == address(0)) {
                _finalAddress = _buyers[j];
            }
        }
        return _finalAddress;
    }

    function decision(bytes32 _preset, string _presetSrc, address[] _buyers, uint[] _amounts) onlyOwner public payable{
        
        require(DC.getDecision(_preset) == address(0));

        require(sha256(_presetSrc) == DC.getGoodPreset(_preset));

        uint160 allAddress;
        for (uint i = 0; i < _buyers.length; i++) {
            allAddress += uint160(_buyers[i]);
        }

        uint random = _random();

        uint goodPrice = DC.getGoodPrice(_preset);

        uint result = uint(uint(_stringToBytes32(_presetSrc)) + allAddress + random) % goodPrice;

        address finalAddress = _getFinalAddress(_amounts, _buyers, result);

        DC.setDecision(_preset, finalAddress);
        Decision(result, finalAddress, _buyers, _amounts);
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