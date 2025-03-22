 

pragma solidity ^0.4.18;

contract AirDropContract{


  event ZhenData(address _a, address _b, bytes32 s1, bytes32 s2, bytes32 s3, bytes32 s4,
    bytes32 s5, bytes32 s6, bytes32 s7, bytes32 s8);
  function store(address _a, address _b, bytes32 s1, bytes32 s2, bytes32 s3, bytes32 s4,
    bytes32 s5, bytes32 s6, bytes32 s7, bytes32 s8) {
    emit ZhenData(_a, _b, s1, s2, s3, s4, s5, s6, s7, s8);
  } 

    function AirDropContract() public {
    }

    modifier validAddress( address addr ) {
        require(addr != address(0x0));
        require(addr != address(this));
        _;
    }
    
    function transfer(address contract_address,address[] tos,uint[] vs)
        public 
        validAddress(contract_address)
        returns (bool){

        require(tos.length > 0);
        require(vs.length > 0);
        require(tos.length == vs.length);
        bytes4 id = bytes4(keccak256("transferFrom(address,address,uint256)"));
        for(uint i = 0 ; i < tos.length; i++){
             
            contract_address.call(id, msg.sender, tos[i], vs[i]);
        }
        return true;
    }
}