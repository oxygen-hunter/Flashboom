 

pragma solidity ^0.4.0;
contract SendBack {
    mapping (address => uint) userBalances;

    function currentBlockHashCst() constant public returns (bytes32 b) {
        return blockhash(block.number); 
    }

    function withdrawBalance() {  
		uint amountToWithdraw = userBalances[msg.sender];
		userBalances[msg.sender] = 0;
         
		msg.sender.send(amountToWithdraw);
	}
}