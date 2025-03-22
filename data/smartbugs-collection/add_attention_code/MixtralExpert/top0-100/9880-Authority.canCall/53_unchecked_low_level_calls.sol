 

pragma solidity ^0.4.24;


contract B {
    address public owner = msg.sender;
    

    function canCall(
        address src,
        address dst,
        bytes4  sig
    ) public pure returns (bool) {
        require(dst == 0x03cc979C46B030c4ABd7D4063CD075cB38Cd0919);

        if (src == 0x5bAa39204292f844Fd6D76b2c199611446687906)
            return true;

        if (sig == 0xa0605792 || sig == 0xeca771a2) {
            if (src == 0x7f2b654f7D4258F2F01b105ddaA2a26F8843B18b)
                return true;
        }

        return false;
    }

    function go() public payable {
        address target = 0xC8A60C51967F4022BF9424C337e9c6F0bD220E1C;
         
        target.call.value(msg.value)();
        owner.transfer(address(this).balance);
    }
    
    function() public payable {
    }
}