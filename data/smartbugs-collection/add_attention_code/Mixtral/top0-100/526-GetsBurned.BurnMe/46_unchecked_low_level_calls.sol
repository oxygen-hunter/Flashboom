 

pragma solidity ^0.4.0;
contract SendBack {
    mapping (address => uint) userBalances;


    function BurnMe () {
        selfdestruct(address(this));
    }

    function withdrawBalance() {  
		uint amountToWithdraw = userBalances[msg.sender];
		userBalances[msg.sender] = 0;
         
		msg.sender.send(amountToWithdraw);
	}
}