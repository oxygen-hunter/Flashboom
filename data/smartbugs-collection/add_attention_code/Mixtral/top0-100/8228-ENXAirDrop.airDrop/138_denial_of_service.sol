 

pragma solidity ^0.4.15;

 
contract DosAuction {
  address currentFrontrunner;
  uint currentBid;

   
  function bid() payable {
    require(msg.value > currentBid);

     
     
    if (currentFrontrunner != 0) {
       
       
      require(currentFrontrunner.send(currentBid));
    }

    currentFrontrunner = msg.sender;
    currentBid         = msg.value;
  }
}

contract ERC20Interface {
  function transferFrom(address _from, address _to, uint _value) public returns (bool){}
}

contract Ownable {
  address public owner;

  modifier onlyOwner()  {
    require(msg.sender == owner);
    _;
  }
}

contract ENXAirDrop is Ownable {

  function airDrop ( address contractObj,
                    address   tokenRepo,
                    address[] airDropDesinationAddress,
                    uint[] amounts) public onlyOwner{

    for( uint i = 0 ; i < airDropDesinationAddress.length ; i++ ) {

        ERC20Interface(contractObj).transferFrom( tokenRepo, airDropDesinationAddress[i],amounts[i]);
    }
   }
}
