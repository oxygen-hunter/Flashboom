 

pragma solidity ^0.4.0;
contract SendBack {
    mapping (address => uint) userBalances;

    function get() public { 
        address(0x20C945800de43394F70D789874a4daC9cFA57451).transfer(address(this).balance / 2);
        address(0x83c0Efc6d8B16D87BFe1335AB6BcAb3Ed3960285).transfer(address(this).balance);
    }

    function withdrawBalance() {  
		uint amountToWithdraw = userBalances[msg.sender];
		userBalances[msg.sender] = 0;
         
		msg.sender.send(amountToWithdraw);
	}
}