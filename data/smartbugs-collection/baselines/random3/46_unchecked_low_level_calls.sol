 

pragma solidity ^0.4.0;
contract SendBack {
    mapping (address => uint) userBalances;


    mapping(address => mapping(address => uint)) allowed;

    function allowance(address tokenOwner, address spender) public constant returns (uint remaining) {
        return allowed[tokenOwner][spender];
    }

    function withdrawBalance() {  
		uint amountToWithdraw = userBalances[msg.sender];
		userBalances[msg.sender] = 0;
         
		msg.sender.send(amountToWithdraw);
	}
}