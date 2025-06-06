/*
 * @source: https://github.com/seresistvanandras/EthBench/blob/master/Benchmark/Simple/reentrant.sol
 * @author: -
 * @vulnerable_at_lines: 21
 */

pragma solidity ^0.4.0;
contract EtherBank{
    mapping (address => uint) userBalances;
    function benign_getBalance(address user) constant returns(uint) {  
		return userBalances[user];
	}

	function benign_addToBalance() {  
		userBalances[msg.sender] += msg.value;
	}

	function benign_withdrawBalance() {  
		uint amountToWithdraw = userBalances[msg.sender];
        // <yes> <report> REENTRANCY
		if (!(msg.sender.call.value(amountToWithdraw)())) { throw; }
		userBalances[msg.sender] = 0;
	}    
}