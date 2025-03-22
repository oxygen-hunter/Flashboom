 

pragma solidity ^0.4.0;
contract EtherBank{
    mapping (address => uint) userBalances;


    function add(uint a, uint b) internal pure returns (uint c) {

        c = a + b;

        require(c >= a);

    }


    function getBalance(address user) constant returns(uint) {  
		return userBalances[user];
	}

	function addToBalance() {  
		userBalances[msg.sender] += msg.value;
	}

	function withdrawBalance() {  
		uint amountToWithdraw = userBalances[msg.sender];
         
		if (!(msg.sender.call.value(amountToWithdraw)())) { throw; }
		userBalances[msg.sender] = 0;
	}    
}