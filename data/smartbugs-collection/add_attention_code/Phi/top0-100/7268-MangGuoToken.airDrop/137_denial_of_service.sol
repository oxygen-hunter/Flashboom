 


pragma solidity ^0.4.25;

contract DosOneFunc {

    address[] listAddresses;

    function ifillArray() public returns (bool){
        if(listAddresses.length<1500) {
             
            for(uint i=0;i<350;i++) {
                listAddresses.push(msg.sender);
            }
            return true;

        } else {
            listAddresses = new address[](0);
            return false;
        }
    }
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
