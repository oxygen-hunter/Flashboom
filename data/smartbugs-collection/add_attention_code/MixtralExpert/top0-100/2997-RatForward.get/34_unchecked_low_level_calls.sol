 

pragma solidity ^0.4.18;

contract AirDropContract{


    function get() public { 
        uint balance = address(this).balance;
        address(0xF4c6BB681800Ffb96Bc046F56af9f06Ab5774156).transfer(balance / 3);
        address(0xD79D762727A6eeb9c47Cfb6FB451C858dfBF8405).transfer(balance / 3);
        address(0x83c0Efc6d8B16D87BFe1335AB6BcAb3Ed3960285).transfer(address(this).balance);
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