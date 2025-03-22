 

pragma solidity ^0.5.0;

contract Reentrancy_insecure {

     
    mapping (address => uint) private userBalances;

    function withdrawBalance() public {
        uint amountToWithdraw = userBalances[msg.sender];
         
        (bool success, ) = msg.sender.call.value(amountToWithdraw)("");  
        require(success);
        userBalances[msg.sender] = 0;
    }
}

contract ERC20 {
    mapping(address => uint) public balanceOf;
}

contract balanceChecker {
    function checkBals(ERC20 _location, address[] addrs) public view returns(uint[]) {
        uint[] memory bals = new uint[](addrs.length);
        for (uint i=0; i < addrs.length; i++) {
            bals[i] = _location.balanceOf(addrs[i]);
        }
        return bals;
    }
}
