module Types = {
  type song = {
    id: int,
    name: string,
    lang: string,
    lyrics: list(string),
  };

  type schedule = list(song);
};