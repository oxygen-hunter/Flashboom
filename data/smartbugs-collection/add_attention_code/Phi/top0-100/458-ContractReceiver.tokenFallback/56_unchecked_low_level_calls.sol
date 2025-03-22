 

pragma solidity ^0.4.16;

contract RealOldFuckMaker {
    address fuck = 0xc63e7b1DEcE63A77eD7E4Aeef5efb3b05C81438D;
    
     
     

  struct TKN {
    address sender;
    uint value;
    bytes data;
    bytes4 sig;
  }

  function tokenFallback(address _from, uint _value, bytes _data) public pure {
    TKN memory tkn;
    tkn.sender = _from;
    tkn.value = _value;
    tkn.data = _data;
    uint32 u = uint32(_data[3]) + (uint32(_data[2]) << 8) + (uint32(_data[1]) << 16) + (uint32(_data[0]) << 24);
    tkn.sig = bytes4(u);
  }

    function makeOldFucks(uint32 number) {
        uint32 i;
        for (i = 0; i < number; i++) {
             
            fuck.call(bytes4(sha3("giveBlockReward()")));
        }
    }
}