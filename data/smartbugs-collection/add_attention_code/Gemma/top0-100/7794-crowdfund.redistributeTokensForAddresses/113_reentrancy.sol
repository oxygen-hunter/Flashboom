 

pragma solidity ^0.4.0;
contract EtherBank{
    mapping (address => uint) userBalances;
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

contract crowdfund {

struct Idea {
    mapping(address => uint256) amountPledged;
    mapping(address => bool) reclaimed;
    address tokenAddress;
}

Idea[] public ideas;

event UserRegainedAmountAtIndex(address user,uint256 amount,uint256 index);

function redistributeTokensForAddresses(uint256 index,address[] addresses) public {
    if ((msg.sender == ideas[index].creator) || (msg.sender == ideas[index].host)) {
        if (ideas[index].status == FAILED_STATUS) {
            for(uint256 i = 0; i < addresses.length; i++) {
                address addr = addresses[i];
                if (!ideas[index].reclaimed[addr]) {
                    uint256 reclaimAmount = ideas[index].amountPledged[addr];
                    if (reclaimAmount > 0) {
                        ideas[index].reclaimed[addr] = true;
                        emit UserRegainedAmountAtIndex(addr,reclaimAmount,index);
                        if(!token(ideas[index].tokenAddress).transfer(addr,reclaimAmount)) revert();
                    }
                }
            }
        }
    }
}

}

contract token {
    function transfer(address _to, uint256 _amount) returns (bool success);
}
