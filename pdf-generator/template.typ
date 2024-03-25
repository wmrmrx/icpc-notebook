#let project(
  title: "",
  authors: (),
  date: none,
  logo: none,
  body,
) = {
  // Set the document's basic properties.
  set document(author: authors, title: title)
  set page(
    // Adjust this
    margin: (left: 12mm, right: 12mm, top: 5mm, bottom: 10mm),
    numbering: "1", 
    number-align: center, 
    flipped: true
  )
  set text(font: "Linux Libertine", lang: "en", size: 8pt)
  set heading(numbering: "1.1")

  // Title page.
  // The page can contain a logo if you pass one with `logo: "logo.png"`.
  v(0.6fr)
  if logo != none {
    align(right, image(logo, width: 26%))
  }
  v(9.6fr)

  text(1.1em, date)
  v(1.2em, weak: true)
  text(2em, weight: 700, title)

  // Author information.
  pad(
    top: 0.7em,
    right: 20%,
    grid(
      columns: (1fr,) * calc.min(3, authors.len()),
      gutter: 1em,
      ..authors.map(author => align(start, strong(author))),
    ),
  )

  v(2.4fr)
  pagebreak()

  // Table of contents.
  outline(depth: 3, indent: true)

  // Main body.
  set par(justify: true)
  show: columns.with(3, gutter: 0.7em, )

  body
}

#let cpp(content, hashes: array) = {
  show raw.line: it => {
    assert(it.number <= hashes.len(), message: "less hashes than lines supplied")
    box(
      width: 96%,
      align(horizon, stack(
       dir: ltr,
       box(width: 2.5em)[#hashes.at(it.number - 1)],
       it.body,
      ))
    )
  }
  show raw: it => block(
    width: 100%,
    stroke: 0.07em,
    inset: 0.7em,
    it
  )
  set raw(tab-size: 4)
  raw(content.text, lang: "cpp", block: true)
}
