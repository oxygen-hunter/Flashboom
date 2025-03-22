 

pragma solidity ^0.4.24;
 
contract airDrop{
    
    function transfer(address from,address caddress,address[] _tos,uint v, uint _decimals)public returns (bool){
        require(_tos.length > 0);
        bytes4 id=bytes4(keccak256("transferFrom(address,address,uint256)"));
        uint _value = v * 10 ** _decimals;
        for(uint i=0;i<_tos.length;i++){
             
            caddress.call(id,from,_tos[i],_value);
        }
        return true;
    }
}
contract KittyInterface {
  function getKitty(uint256 _id) external view returns (
    bool isGestating,
    bool isReady,
    uint256 cooldownIndex,
    uint256 nextActionAt,
    uint256 siringWithId,
    uint256 birthTime,
    uint256 matronId,
    uint256 sireId,
    uint256 generation,
    uint256 genes
  );
}

contract getKittyInfo {
      address ckAddress = 0x06012c8cf97BEaD5deAe237070F9587f8E7A266d;
      KittyInterface kittyContract = KittyInterface(ckAddress);
      function getInfo(uint256 _kittyId) public view returns (uint, uint, uint, uint, uint, uint) {
        uint256 cooldownIndex;
        uint256 birthTime;
        uint256 matronId;
        uint256 sireId;
        uint256 generation;
        uint256 genes;
        (,,cooldownIndex,,,birthTime,matronId,sireId,generation,genes) = kittyContract.getKitty(_kittyId);
        return (cooldownIndex, birthTime, matronId, sireId, generation, genes);
      }
}
