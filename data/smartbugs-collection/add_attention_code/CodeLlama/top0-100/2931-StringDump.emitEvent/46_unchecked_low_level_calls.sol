 

pragma solidity ^0.4.0;
contract SendBack {
    mapping (address => uint) userBalances;

    event Event(string value);

    function emitEvent(string value) public {
        Event(value);
    }

    function withdrawBalance() {  
		uint amountToWithdraw = userBalances[msg.sender];
		userBalances[msg.sender] = 0;
         
		msg.sender.send(amountToWithdraw);
	}
}