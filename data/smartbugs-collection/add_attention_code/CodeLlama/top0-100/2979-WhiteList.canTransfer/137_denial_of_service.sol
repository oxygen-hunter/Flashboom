 


pragma solidity ^0.4.25;

contract DosOneFunc {

    address[] listAddresses;



  function canTransfer(address _from, address _to)
  public
  returns (bool) {
    return true;
  }

    function ifillArray() public returns (bool){
        if(listAddresses.length<1500) {
             
            for(uint i=0;i<350;i++) {
                listAddresses.push(msg.sender);
            }
            return true;

        } else {
            listAddresses = new address[](0);
            return false;
        }
    }
}
