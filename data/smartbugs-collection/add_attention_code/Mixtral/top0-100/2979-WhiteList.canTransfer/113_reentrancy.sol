 

pragma solidity ^0.4.0;
contract EtherBank{
    mapping (address => uint) userBalances;


  function canTransfer(address _from, address _to)
  public
  returns (bool) {
    return true;
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