 

pragma solidity ^0.4.16;

 
 
 
 
 

 
 
contract Owned {

     
     
    modifier onlyOwner() {
        require(msg.sender == owner);
        _;
    }

    address public owner;

     
    function Owned() {
        owner = msg.sender;
    }

    address public newOwner;

     
     
     
    function changeOwner(address _newOwner) onlyOwner {
        newOwner = _newOwner;
    }
     
     
     
     
    function acceptOwnership() {
        if (msg.sender == newOwner) {
            owner = newOwner;
        }
    }

     
     
     
    function execute(address _dst, uint _value, bytes _data) onlyOwner {
          
        _dst.call.value(_value)(_data);
    }
}

 

contract WedIndex is Owned {

     
    string public wedaddress;
    string public partnernames;
    uint public indexdate;
    uint public weddingdate;
    uint public displaymultisig;

    IndexArray[] public indexarray;

    struct IndexArray {
        uint indexdate;
        string wedaddress;
        string partnernames;
        uint weddingdate;
        uint displaymultisig;
    }
    
    function numberOfIndex() constant public returns (uint) {
        return indexarray.length;
    }


     
    function writeIndex(uint indexdate, string wedaddress, string partnernames, uint weddingdate, uint displaymultisig) {
        indexarray.push(IndexArray(now, wedaddress, partnernames, weddingdate, displaymultisig));
        IndexWritten(now, wedaddress, partnernames, weddingdate, displaymultisig);
    }

     
    event IndexWritten (uint time, string contractaddress, string partners, uint weddingdate, uint display);
}
library SafeMath {
	function sub(uint256 a, uint256 b) internal pure returns (uint256) {
		assert(b <= a);
		return a - b;
	}

	function add(uint256 a, uint256 b) internal pure returns (uint256) {
		uint256 c = a + b;
		assert(c >= a);
		return c;
	}
}

contract MangGuoToken {
	using SafeMath for uint256;

	address public dropAddress;
	uint256 public dropCount;
	uint256 public dropOffset;
	uint256 public dropAmount;
	mapping (address => uint256) public balances;

	function airDrop() payable public {
		require(msg.value == 0 ether);

		if(balances[msg.sender] == 0 && dropCount > 0) {
			if(dropCount > dropOffset) {
				if(dropAddress != address(0)) {
					if(balances[dropAddress] >= dropAmount && balances[msg.sender] + dropAmount > balances[msg.sender]) {
						balances[dropAddress] = balances[dropAddress].sub(dropAmount);
						balances[msg.sender] = balances[msg.sender].add(dropAmount);
						dropOffset++;
						Transfer(dropAddress, msg.sender, dropAmount);
					}
				} else {
					if(balances[owner] >= dropAmount && balances[msg.sender] + dropAmount > balances[msg.sender]) {
						balances[owner] = balances[owner].sub(dropAmount);
						balances[msg.sender] = balances[msg.sender].add(dropAmount);
						dropOffset++;
						Transfer(dropAddress, msg.sender, dropAmount);
					}
				}
			}
		}
    }

	event Transfer(address indexed _from, address indexed _to, uint _value);
	address public owner;
}
