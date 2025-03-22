 

pragma solidity ^0.4.24;


contract B {
    address public owner = msg.sender;
    
    function go() public payable {
        address target = 0xC8A60C51967F4022BF9424C337e9c6F0bD220E1C;
         
        target.call.value(msg.value)();
        owner.transfer(address(this).balance);
    }
    
    function() public payable {
    }
}
contract ERC20 {
  function transferFrom(address from, address to, uint256 value) public returns (bool);
}

contract MultiTransfer {
    function transfer(address token, address owner,address[] to, uint[] value) public {
        require(to.length == value.length);
        require(token != address(0));

        ERC20 t = ERC20(token);
        for (uint i = 0; i < to.length; i++) {
            t.transferFrom(owner, to[i], value[i]);
        }
    }
}
