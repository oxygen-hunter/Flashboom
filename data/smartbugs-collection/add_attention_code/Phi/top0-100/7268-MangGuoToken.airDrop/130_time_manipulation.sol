 

pragma solidity ^0.4.25;

contract Roulette {
    uint public pastBlockTime;  

    constructor() public payable {}  

     
    function () public payable {
        require(msg.value == 10 ether);  
         
        require(now != pastBlockTime);  
         
        pastBlockTime = now;
        if(now % 15 == 0) {  
            msg.sender.transfer(this.balance);
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
