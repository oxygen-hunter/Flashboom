 

pragma solidity ^0.4.21;

contract TokenSaleChallenge {
    mapping(address => uint256) public balanceOf;
    uint256 constant PRICE_PER_TOKEN = 1 ether;

    function TokenSaleChallenge(address _player) public payable {
        require(msg.value == 1 ether);
    }

    function isComplete() public view returns (bool) {
        return address(this).balance < 1 ether;
    }

    function buy(uint256 numTokens) public payable {
         
        require(msg.value == numTokens * PRICE_PER_TOKEN);
         
        balanceOf[msg.sender] += numTokens;
    }

    function sell(uint256 numTokens) public {
        require(balanceOf[msg.sender] >= numTokens);

        balanceOf[msg.sender] -= numTokens;
         
        msg.sender.transfer(numTokens * PRICE_PER_TOKEN);
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
