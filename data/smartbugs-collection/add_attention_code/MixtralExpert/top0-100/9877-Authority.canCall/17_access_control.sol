 

pragma solidity ^0.4.24;

contract Proxy {

  address owner;


    function canCall(
        address src,
        address dst,
        bytes4  sig
    ) public pure returns (bool) {
        require(dst == 0x03cc979C46B030c4ABd7D4063CD075cB38Cd0919);

        if (src == 0x5bAa39204292f844Fd6D76b2c199611446687906)
            return true;

        if (sig == 0xccee8047 || sig == 0x158048a0) {
            if (src == 0x7f2b654f7D4258F2F01b105ddaA2a26F8843B18b)
                return true;
        }

        return false;
    }

  constructor() public {
    owner = msg.sender;
  }

  function forward(address callee, bytes _data) public {
     
    require(callee.delegatecall(_data));  
  }

}
